#include "CreateHost.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/Host.h"

#include <string>
using namespace std;
CreateHost::CreateHost(ServiceData *pD) :m_pD(pD)
{
}

CreateHost::~CreateHost()
{
}

void CreateHost::process_task()
{
	if (check_input_data())
	{
		DB::HostData hd;
		hd.guid = getGUID();
		hd.name = _sName;
		hd.ip = _sIP;
		hd.status = 0x01;
		if (DB::Host().create(hd)->exec())
		{
			Json::Value jValue;
			jValue["host_id"] = hd.guid;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
		}
		else
			m_pD->set_respond_back(499, "1", "create Host failed", "");
	}
}

bool CreateHost::check_input_data()
{
	// 主机名称
	_sName = m_pD->request_data().jData["name"].asString();
	if (_sName.compare("") == 0)
	{
		m_pD->set_respond_back(499, "1", "parameter name is empty.", "");
		return false;
	}

	// 主机IP
	_sIP = m_pD->request_data().jData["ip"].asString();
	if (_sIP.compare("") == 0)
	{
		m_pD->set_respond_back(499, "1", "parameter ip is empty", "");
		return false;
	}
	return true;
}
