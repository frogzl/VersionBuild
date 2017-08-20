#include "QueryExecutableRole.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
#include "../Database/Executable_Role.h"

QueryExecutableRole::QueryExecutableRole(ServiceData *pD) :m_pD(pD)
{
}


QueryExecutableRole::~QueryExecutableRole()
{
}

void QueryExecutableRole::process_task()
{
	string sExecutableRoleID = m_pD->request_data().vecParameters[0];
	if (sExecutableRoleID.compare("") == 0)
	{
		vector<DB::Executable_RoleData> *pVecERs = DB::Executable_Role().query()->all();
		if (pVecERs)
		{
			Json::Value jValue;
			for (int nIndex = 0; nIndex < pVecERs->size(); nIndex++)
			{
				Json::Value jHost;
				jValue["guid"] = (*pVecERs)[nIndex].guid;
				jValue["name"] = (*pVecERs)[nIndex].name;
				jValue["description"] = (*pVecERs)[nIndex].description;
				jValue.append(jValue);
			}
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
			delete pVecERs;
		}
		else
			m_pD->set_respond_back(499, "1", "Executable_Role table is empty.", "");
	}
	else
	{
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", sExecutableRoleID));
		DB::Executable_RoleData *pERD = DB::Executable_Role().query()->where(conditions)->first();
		if (pERD)
		{
			Json::Value jValue;
			jValue["guid"] = pERD->guid;
			jValue["name"] = pERD->name;
			jValue["description"] = pERD->description;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
			delete pERD;
		}
		else
		{
			char szBuf[255];
			sprintf(szBuf, "query failed %s.", sExecutableRoleID.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
		}
	}
}