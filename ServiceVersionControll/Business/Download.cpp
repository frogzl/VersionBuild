#include "Download.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/Storage.h"
#include "../Database/Block.h"
#include <string>
using namespace std;
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
	}
}

bool Download::check_input_data()
{
	// �ļ���
	_sFileName = "";

	// Ψһ��ʶ
	_sStorageID = m_pD->request_data().vecParameters[0];

	// ����Rangeͷ��Ϣ
	string sRange = m_pD->request_data().mHeaders["range"];
	sscanf_s(sRange.c_str(), "bytes %I64d-%I64d/%I64d", &_llStart, &_llEnd, &_llTotal);

	return true;
}
