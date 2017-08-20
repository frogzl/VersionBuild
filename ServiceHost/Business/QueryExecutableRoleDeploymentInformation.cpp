#include "QueryExecutableRoleDeploymentInformation.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
#include "../Database/Executable_Role_Deploy.h"

QueryExecutableRoleDeploymentInformation::QueryExecutableRoleDeploymentInformation(ServiceData *pD) :m_pD(pD)
{
}


QueryExecutableRoleDeploymentInformation::~QueryExecutableRoleDeploymentInformation()
{
}

void QueryExecutableRoleDeploymentInformation::process_task()
{
	string sExecutableRoleDeployID = m_pD->request_data().vecParameters[0];
	if (sExecutableRoleDeployID.compare("") == 0)
	{
		vector<DB::Executable_Role_DeployData> *pVecERDs = DB::Executable_Role_Deploy().query()->all();
		if (pVecERDs)
		{
			Json::Value jValue;
			for (int nIndex = 0; nIndex < pVecERDs->size(); nIndex++)
			{
				Json::Value jHost;
				jValue["guid"] = (*pVecERDs)[nIndex].guid;
				jValue["host_id"] = (*pVecERDs)[nIndex].host_id;
				jValue["executable_role_id"] = (*pVecERDs)[nIndex].executable_role_id;
				jValue["port"] = (*pVecERDs)[nIndex].port;
				jValue["status"] = (*pVecERDs)[nIndex].status;
				jValue.append(jValue);
			}
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
			delete pVecERDs;
		}
		else
			m_pD->set_respond_back(499, "1", "Executable_Role_Deploy table is empty.", "");
	}
	else
	{
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", sExecutableRoleDeployID));
		DB::Executable_Role_DeployData *pERDD = DB::Executable_Role_Deploy().query()->where(conditions)->first();
		if (pERDD)
		{
			Json::Value jValue;
			jValue["guid"] = pERDD->guid;
			jValue["host_id"] = pERDD->host_id;
			jValue["executable_role_id"] = pERDD->executable_role_id;
			jValue["port"] = pERDD->port;
			jValue["status"] = pERDD->status;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
			delete pERDD;
		}
		else
		{
			char szBuf[255];
			sprintf(szBuf, "query failed %s.", sExecutableRoleDeployID.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
		}
	}
}