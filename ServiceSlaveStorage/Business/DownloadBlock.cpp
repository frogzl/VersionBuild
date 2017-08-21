#include "DownloadBlock.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include <string>
using namespace std;
DownloadBlock::DownloadBlock(ServiceData *pD) :m_pD(pD)
{
}

DownloadBlock::~DownloadBlock()
{
}

void DownloadBlock::process_task()
{
	char szBuf[255];
	if (check_input_data())
	{
		FILE *fp = fopen(_sPath.c_str(), "rb");
		if (fp)
		{
			char *szTmp = new char[_llEnd - _llStart + 2];
			fseek(fp, _llStart, SEEK_SET);
			size_t stRead = fread(szTmp, 1, _llEnd - _llStart + 1, fp);
			fclose(fp);

			Json::Value jData;
			jData["data"] = Base64_Encode(szBuf, stRead);
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jData);
		}
		else
		{
			sprintf(szBuf, "file %s is not found.", _sPath.c_str());
			m_pD->set_respond_back(499, "1", "requires path arguments.", "");
		}
	}
}

bool DownloadBlock::check_input_data()
{
	// 解析Range头信息
	string sRange = m_pD->request_data().mHeaders["range"];
	sscanf_s(sRange.c_str(), "bytes %I64d-%I64d", &_llStart, &_llEnd);

	// 获取path
	_sPath = m_pD->request_data().mConditions["path"];
	if (_sPath.compare("") == 0)
	{
		m_pD->set_respond_back(499, "1", "requires path arguments.", "");
		return false;
	}
	return true;
}
