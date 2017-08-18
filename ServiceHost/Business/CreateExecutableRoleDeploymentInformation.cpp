#include "CreateExecutableRoleDeploymentInformation.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/Executable_Role_Deploy.h"

CreateExecutableRoleDeploymentInformation::CreateExecutableRoleDeploymentInformation(ServiceData *pD) :m_pD(pD)
{
}


CreateExecutableRoleDeploymentInformation::~CreateExecutableRoleDeploymentInformation()
{
}

void CreateExecutableRoleDeploymentInformation::process_task()
{
	if (check_input_data())
	{
		DB::Executable_Role_DeployData erdd;
		erdd.guid = getGUID();
		erdd.host_id = _sHostID;
		erdd.executable_role_id = _sExecutableRoleID;
		erdd.port = _nPort;
		erdd.status = 0x01;
		if (DB::Executable_Role_Deploy().create(erdd)->exec())
		{
			Json::Value jValue;
			jValue["executable_role_deploy_id"] = erdd.guid;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
		}
		else
			m_pD->set_respond_back(499, "1", "create Executable_Role_Deploy failed.", "");

	}
}

bool CreateExecutableRoleDeploymentInformation::check_input_data()
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
