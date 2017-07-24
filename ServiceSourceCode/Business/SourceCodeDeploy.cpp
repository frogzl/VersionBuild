#include "SourceCodeDeploy.h"
#include "../Exception/HttpRequestException.h"
#include "../Tools/HttpClient.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Deploy.h"
#include "../Database/Resource_Host.h"
SourceCodeDeploy::SourceCodeDeploy(BusinessInterface *pB) :m_pB(pB)
{
}

SourceCodeDeploy::~SourceCodeDeploy()
{
}

void SourceCodeDeploy::process_task()
{
	string sPath = "/buildrule/deploy";
	string sID = m_pB->request_data().jData["id"].asString();

	// �ҵ�����δ������߲���ʧ�ܵ�buildrule
	char *szCondition = new char[255];
	sprintf(szCondition, " `sourcecodeid`=\"%s\" and `status` in (0,99)", sID.c_str());
	vector<DB::BuildRuleData> *pBuildRules = DB::BuildRule().query()->where(szCondition)->all();
	delete [] szCondition;
	if (pBuildRules)
	{
		for (int nIndex = 0; nIndex < pBuildRules->size(); nIndex++)
		{
			DB::BuildRuleData &brd = (*pBuildRules)[nIndex];
			DB::Conditions conditions;
			conditions.insert(pair<string, string>("guid", brd.deployid));
			DB::BuildRule_DeployData *pBRDD = DB::BuildRule_Deploy().query()->where(conditions)->first();
			if (!pBRDD)
			{
				m_pB->set_respond_back(HTTP_INTERNAL, "1", "BuildRule_DeployData failed", "");
				return;
			}

			conditions.clear();
			conditions.insert(pair<string, string>("guid", pBRDD->deployhostid));
			DB::Resource_HostData *pHD = DB::Resource_Host().query()->where(conditions)->first();
			if (!pHD)
			{
				m_pB->set_respond_back(HTTP_INTERNAL, "1", "Resource_HostData failed", "");
				return;
			}


			// �����������
			Json::Value jsonPost;
			jsonPost["sourcecodeid"] = sID;
			jsonPost["buildruleid"] = brd.guid;
			jsonPost["localpath"] = pBRDD->deploypath;

			HttpClient http;
			http.post(pHD->address, pHD->port, sPath, Json::FastWriter().write(jsonPost));
		}
	}
	m_pB->set_respond_back(HTTP_OK, "0", "create sourcecode resource success!", "");
}