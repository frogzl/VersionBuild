#include "QueryHost.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
QueryHost::QueryHost(ServiceData *pD) :m_pD(pD)
{
}

QueryHost::~QueryHost()
{
}

void QueryHost::process_task()
{
}

bool QueryHost::check_input_data()
{
	// 主机名称
	if (m_pD->request_data().jData["executable_role_id"].isString())
		_sExecutableRoleID = m_pD->request_data().jData["executable_role_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "parameter executable_role_id is empty.", "");
		return false;
	}

	// 主机IP
	if (m_pD->request_data().jData["host_id"].isString())
		_sHostID = m_pD->request_data().jData["host_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "parameter host_id is empty", "");
		return false;
	}

	// 主机IP
	if (m_pD->request_data().jData["port"].isInt())
		_nPort = m_pD->request_data().jData["port"].asInt();
	else
	{
		m_pD->set_respond_back(499, "1", "parameter port is empty", "");
		return false;
	}
	return true;
}
