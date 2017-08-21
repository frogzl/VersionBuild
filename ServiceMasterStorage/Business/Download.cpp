#include "Download.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/Storage.h"
#include "../Database/Block.h"
#include  "Helper.h"
#include <string>
using namespace std;
using namespace Helper;
Download::Download(ServiceData *pD) :m_pD(pD)
{
}

Download::~Download()
{
}

void Download::process_task()
{
	char szBuf[255];
	if (check_input_data())
	{
		sprintf(szBuf, " `guid`=\"%s\" and `status`=0x02 ", _sStorageID.c_str());
		DB::StorageData *pSD = DB::Storage().query()->where(szBuf)->first();
		if (pSD)
		{
			_llTotal = pSD->size;
			if (_llEnd == 0)
				_llEnd = _llTotal - 1;

			sprintf(szBuf, " `storage_id`=\"%s\" and (`start`>=%I64d and `start`<=%I64d) or (`end`>=%I64d and `end`<=%I64d)", _sStorageID.c_str(), _llStart, _llEnd, _llStart, _llEnd);
			vector<DB::BlockData> *pBlocks = DB::Block().query()->where(szBuf)->all();
			if (pBlocks)
			{
				int nCount = pBlocks->size();
				bool bRet = false;
				char *szData = new char[_llEnd - _llStart + 1];
				long long llMax = 0;
				for (int nIndex = 0; nIndex < nCount; nIndex++)
				{
					DB::BlockData &bd = (*pBlocks)[nIndex];
					Network::Request_Data rd;
					rd.mConditions.insert(pair<string, string>("hs", bd.proxy_host_id));
					rd.mConditions.insert(pair<string, string>("ss", bd.server_host_id));
					rd.mConditions.insert(pair<string, string>("path", bd.path));
					long long llStart = 0;
					if (_llStart <= bd.start)
						llStart = 0;
					else if (_llStart <= bd.end)
						llStart = _llStart - bd.start;
					else
						llStart = bd.end - bd.start;

					long long llEnd = 0;
					if (_llEnd >= bd.end)
						llEnd = bd.end - bd.start;
					else if (_llEnd >= bd.start)
						llEnd = _llEnd - bd.start;
					else
						llEnd = 0;
					sprintf(szBuf, "bytes %I64d-%I64d", &llStart, &llEnd);
					rd.mHeaders.insert(pair<string, string>("guid", szBuf));
					sprintf(szBuf, "/file/{%s}/block", _sStorageID.c_str());

					if (bd.start <= _llStart)
						bRet = Network::download_block("6b59871e-274e-43ab-ab08-6cedcd60cdd9", "1", szBuf, rd, szData);
					else
						bRet = Network::download_block("6b59871e-274e-43ab-ab08-6cedcd60cdd9", "1", szBuf, rd, szData + bd.start - _llStart);
					
					if (!bRet)
						break;
					if (bd.end >= llMax)
						llMax = bd.end;
				}
				if (bRet)
				{
					long long llRealEnd = (_llEnd <= llMax) ? _llEnd : llMax;
					sprintf(szBuf, "bytes %I64d-%I64d/%I64d", _llStart, llRealEnd, pSD->size);
					m_pD->set_respond_header("range", szBuf);
					Json::Value jValue;
					jValue["data"] = Base64_Encode(szBuf, llRealEnd - _llStart);
					m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
				}
				else
				{
					sprintf(szBuf, "block %s for storage %s is not found.", bd.guid.c_str(), _sStorageID.c_str());
					m_pD->set_respond_back(499, "1", szBuf, "");
				}
				delete[] szData;
				delete pBlocks;
			}
			else
			{
				delete pSD;
				sprintf(szBuf, "available block for storage %s is not found.", _sStorageID.c_str());
				m_pD->set_respond_back(499, "1", szBuf, "");
			}
		}
		else
		{
			sprintf(szBuf, "available storage %s is not found.", _sStorageID.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
		}
	}
}

bool Download::check_input_data()
{
	// 文件名
	_sFileName = "";

	// 唯一标识
	_sStorageID = m_pD->request_data().vecParameters[0];

	// 解析Range头信息
	string sRange = m_pD->request_data().mHeaders["range"];
	sscanf_s(sRange.c_str(), "bytes %I64d-%I64d/%I64d", &_llStart, &_llEnd, &_llTotal);

	return true;
}
