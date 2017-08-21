#include "Upload.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/Storage.h"
#include "../Database/Block.h"
#include <sstream>
using namespace std;
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