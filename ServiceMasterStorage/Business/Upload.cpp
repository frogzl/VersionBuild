#include "Upload.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/Storage.h"
#include "../Database/Block.h"
#include "Helper.h"
#include <sstream>
using namespace std;
using namespace Helper;
Upload::Upload(ServiceData *pD) :m_pD(pD)
{
}


Upload::~Upload()
{
}

/*
 range bytes start-end/total

 如果 start = 0, end = total，则使用本地默认分块策略，每块2MB。
 如果 end != total，则以当前范围为一块存储
 */
void Upload::process_task()
{
	char szBuf[255];
	if (check_input_data())
	{
		if (_llStart == 0 && _llEnd == _llTotal - 1)
			create_first_block();
		else
		{
			if (_llStart == 0)
				create_first_block();
			else
			{
				if (_sStorageID.compare("") == 0)
					m_pD->set_respond_back(499, "1", "storage id is empty.", "");
				else
				{
					DB::Conditions con;
					con.insert(pair<string, string>("guid", _sStorageID));
					DB::StorageData *pSD = DB::Storage().query()->where(con)->first();
					if (pSD)
					{
						// 向slave发送存储请求
						DB::BlockData bd;
						CallBackData cbd;
						cbd.pData = (void*)&bd;
						Network::Request_Data rd;
						rd.sData = Json::FastWriter().write(m_pD->request_data().jData);
						rd.mHeaders.insert(pair<string, string>("range", m_pD->request_data().mHeaders["range"]));
						sprintf(szBuf, "/file/{%s}/block", pSD->guid.c_str());
						if (!Network::post(Network::enReverseProxy, "6b59871e-274e-43ab-ab08-6cedcd60cdd9", "1", szBuf, rd, process_task_callback, &cbd))
						{
							m_pD->set_respond_back(499, "1", cbd._sMsg, "");
							return;
						}

						// 创建block信息
						if (!DB::Block().create(bd)->exec())
						{
							m_pD->set_respond_back(499, "1", "failed to create block info.", "");
							set<string> vecfilter;
							vecfilter.insert("status");
							pSD->status = 0x04;
							DB::Conditions con;
							con.insert(pair<string, string>("guid", pSD->guid));
							DB::Storage().update(vecfilter, *pSD)->where(con)->exec();
							return;
						}

						// 更新storage信息
						while (true)
						{
							set<string> vecfilter;
							vecfilter.insert("size");
							pSD->size += (bd.end - bd.start);
							if (pSD->size == _llTotal)
							{
								vecfilter.insert("status");
								pSD->status = 0x02;
							}

							sprintf(szBuf, "`guid`=\"%s\" and `version`=%d", pSD->guid.c_str(), pSD->version);
							if (DB::Storage().update(vecfilter, *pSD)->where(szBuf)->exec())
								break;
							else
							{
								delete pSD;
								DB::Conditions con;
								con.insert(pair<string, string>("guid", _sStorageID));
								pSD = DB::Storage().query()->where(con)->first();
								if (pSD == NULL)
								{
									sprintf(szBuf, "%s storage is not found when update.", _sStorageID.c_str());
									m_pD->set_respond_back(499, "1", szBuf, "");
									return;
								}
							}
						}

						Json::Value jValue;
						jValue["storage_id"] = pSD->guid;
						m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
						delete pSD;
					}
					else
					{
						sprintf(szBuf, "%s storage is not found.", _sStorageID.c_str());
						m_pD->set_respond_back(499, "1", szBuf, "");
					}
				}
			}
		}
	}
}

bool Upload::check_input_data()
{	
	// 文件名
	if (m_pD->request_data().jData["file_name"].isString())
		_sFileName = m_pD->request_data().jData["file_name"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "file name is empty.", "");
		return false;
	}

	// 唯一标识
	if (m_pD->request_data().jData["storage_id"].isString())
		_sStorageID = m_pD->request_data().jData["storage_id"].asString();
	else
		_sStorageID = "";

	// 解析Range头信息
	string sRange = m_pD->request_data().mHeaders["range"];
	sscanf_s(sRange.c_str(), "bytes %I64d-%I64d/%I64d", &_llStart, &_llEnd, &_llTotal);

	return true;
}

void Upload::create_first_block()
{
	char szBuf[255];
	DB::StorageData sd;
	sd.guid = getGUID();
	sd.file_name = _sFileName;
	sd.size = 0;
	sd.status = 0x01;
	sd.version = 0;
	if (DB::Storage().create(sd)->exec())
	{
		// 向slave发送存储请求
		DB::BlockData bd;
		CallBackData cbd;
		cbd.pData = (void*)&bd;
		Network::Request_Data rd;
		rd.sData = Json::FastWriter().write(m_pD->request_data().jData);
		rd.mHeaders.insert(pair<string, string>("range", m_pD->request_data().mHeaders["range"]));
		sprintf(szBuf, "/file/{%s}/block", sd.guid.c_str());
		if (!Network::post(Network::enReverseProxy, "6b59871e-274e-43ab-ab08-6cedcd60cdd9", "1", szBuf, rd, process_task_callback, &cbd))
		{
			m_pD->set_respond_back(499, "1", cbd._sMsg, "");
			return;
		}

		// 创建block信息
		if (!DB::Block().create(bd)->exec())
		{
			m_pD->set_respond_back(499, "1", "failed to create block info.", "");
			set<string> vecfilter;
			vecfilter.insert("status");
			sd.status = 0x04;
			DB::Conditions con;
			con.insert(pair<string, string>("guid", sd.guid));
			DB::Storage().update(vecfilter, sd)->where(con)->exec();
			return;
		}

		// 更新storage信息
		set<string> vecfilter;
		vecfilter.insert("size");
		sd.size = bd.end - bd.start;
		if (sd.size == _llTotal)
		{
			vecfilter.insert("status");
			sd.status = 0x02;
		}

		sprintf(szBuf, "`guid`=\"%s\" and `version`=%d", sd.guid.c_str(), sd.version);
		while (!DB::Storage().update(vecfilter, sd)->where(szBuf)->exec());

		Json::Value jValue;
		jValue["storage_id"] = sd.guid;
		m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
	}
	else
		m_pD->set_respond_back(499, "1", "create storage record failed.", "");
}

bool Upload::process_task_callback(Network::Respond_Data *pData, void *pArg)
{
	CallBackData &cbd = *(CallBackData*)pArg;
	DB::BlockData &bd = *(DB::BlockData*)(cbd.pData);
	if (pData->nHttpStatus != 200)
		return false;

	Json::Value jData;
	Json::Reader reader;
	if (!reader.parse(pData->sData.c_str(), jData))
		return false;

	stringstream ss;
	bd.guid = jData["guid"].asString();
	bd.storage_id = jData["storage_id"].asString();
	ss << jData["start"].asString();
	ss >> bd.start;
	ss.str("");
	ss.clear();
	ss << jData["end"].asString();
	ss >> bd.end;
	bd.proxy_host_id = jData["proxy_host_id"].asString();
	bd.server_host_id = jData["server_host_id"].asString();
	bd.path = jData["path"].asString();
	return true;
}