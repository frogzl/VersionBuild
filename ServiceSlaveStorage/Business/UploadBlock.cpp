#include "UploadBlock.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../SystemConfig.h"
#include <sstream>
using namespace std;
UploadBlock::UploadBlock(ServiceData *pD) :m_pD(pD)
{
}


UploadBlock::~UploadBlock()
{
}

/*
 range bytes start-end/total

 ��� start = 0, end = total����ʹ�ñ���Ĭ�Ϸֿ���ԣ�ÿ��2MB��
 ��� end != total�����Ե�ǰ��ΧΪһ��洢
 */
void UploadBlock::process_task()
{
	ULONGLONG llBlockSize = _llEnd - _llStart;

	// Ѱ�ҿ��õĴ洢λ��
	string sDir = "";
	for (int nIndex = 0; nIndex < SystemConfig::instance()->vecPartition.size(); nIndex++)
	{
		ULONGLONG llTmp = get_dir_free_size(SystemConfig::instance()->vecPartition[nIndex]);
		if (llTmp > llBlockSize)
		{
			sDir = SystemConfig::instance()->vecPartition[nIndex];
			break;
		}
	}
	if (sDir.compare("") == 0)
	{
		m_pD->set_respond_back(499, "1", "no space for file.", "");
		return;
	}

	// д���ļ�
	sDir += ("\\storage\\" + _sStorageID);
	size_t stReal = Base64_Decode(sDir.c_str(), "wb", m_pD->request_data().jData["data"].asString().c_str(), m_pD->request_data().jData["data"].asString().length());
	if (stReal != 0)
	{
		Json::Value jData;

		jData["guid"] = getGUID();
		jData["storage_id"] = _sStorageID;
		string sSize;
		stringstream ss;
		ss << _llStart;
		ss >> sSize;
		jData["start"] = sSize;
		ss.str("");
		ss.clear();
		ss << _llEnd;
		ss >> sSize;
		jData["end"] = sSize;
		jData["proxy_host_id"] = SystemConfig::instance()->m_sRPSGuid;
		jData["server_host_id"] = SystemConfig::instance()->m_sGuid;
		jData["path"] = sDir;
		m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jData);
	}
	else
		m_pD->set_respond_back(HTTP_INTERNAL, "1", "create file failed!", "");


}

bool UploadBlock::check_input_data()
{	
	// �ļ���
	if (m_pD->request_data().jData["file_name"].isString())
		_sFileName = m_pD->request_data().jData["file_name"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "file name is empty.", "");
		return false;
	}

	// Ψһ��ʶ
	if (m_pD->request_data().jData["storage_id"].isString())
		_sStorageID = m_pD->request_data().jData["storage_id"].asString();
	else
		_sStorageID = "";

	// ����Rangeͷ��Ϣ
	string sRange = m_pD->request_data().mHeaders["range"];
	sscanf_s(sRange.c_str(), "bytes %I64d-%I64d/%I64d", &_llStart, &_llEnd, &_llTotal);

	return true;
}

ULONGLONG UploadBlock::get_dir_free_size(string sDirName)
{
	ULARGE_INTEGER nFreeBytesAvailable;
	ULARGE_INTEGER nTotalNumberOfBytes;
	ULARGE_INTEGER nTotalNumberOfFreeBytes;
	if (GetDiskFreeSpaceExA(sDirName.c_str(), &nFreeBytesAvailable, &nTotalNumberOfBytes, &nTotalNumberOfFreeBytes))
		return nFreeBytesAvailable.QuadPart;
	else
		return 0;
}
