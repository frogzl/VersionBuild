#include "QueryHost.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
#include "../Database/Host.h"

QueryHost::QueryHost(ServiceData *pD) :m_pD(pD)
{
}

QueryHost::~QueryHost()
{
}

void QueryHost::process_task()
{
	std::string sHostID = m_pD->request_data().vecParameters[0];
	if (sHostID.compare("") == 0)
	{
		vector<DB::HostData> *pVecHosts = DB::Host().query()->all();
		if (pVecHosts)
		{
			Json::Value jValue;
			for (int nIndex = 0; nIndex < pVecHosts->size(); nIndex++)
			{
				Json::Value jHost;
				jValue["guid"] = (*pVecHosts)[nIndex].guid;
				jValue["name"] = (*pVecHosts)[nIndex].name;
				jValue["ip"] = (*pVecHosts)[nIndex].ip;
				jValue["status"] = (*pVecHosts)[nIndex].status;
				jValue.append(jValue);
			}
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
			delete pVecHosts;
		}
		else
			m_pD->set_respond_back(499, "1", "host table is empty.", "");
	}
	else
	{
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", sHostID));
		DB::HostData *pHD = DB::Host().query()->where(conditions)->first();
		if (pHD)
		{
			Json::Value jValue;
			jValue["guid"] = pHD->guid;
			jValue["name"] = pHD->name;
			jValue["ip"] = pHD->ip;
			jValue["status"] = pHD->status;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jValue);
			delete pHD;
		}
		else
		{
			char szBuf[255];
			sprintf(szBuf, "query failed %s.", sHostID.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
		}
	}
}