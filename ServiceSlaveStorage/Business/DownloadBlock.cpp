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
	if (check_input_data())
	{
	}
}

bool DownloadBlock::check_input_data()
{
	// Ö÷»úÃû³Æ
	_sName = m_pD->request_data().jData["name"].asString();
	if (_sName.compare("") == 0)
	{
		m_pD->set_respond_back(499, "1", "parameter name is empty.", "");
		return false;
	}

	return true;
}
