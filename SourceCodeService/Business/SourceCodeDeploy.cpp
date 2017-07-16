#include "SourceCodeDeploy.h"
#include "../Exception/HttpRequestException.h"
#include "../Tools/HttpClient.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Deploy.h"
#include "../Database/Resource_Host.h"
SourceCodeDeploy::SourceCodeDeploy()
{
}

SourceCodeDeploy::~SourceCodeDeploy()
{
}

void SourceCodeDeploy::process_task()
{
	string sPath = "/buildrule/deploy";
	string sID = m_rdInData.jData["id"].asString();

	// 找到所有未部署或者部署失败的buildrule
	sprintf(m_szBuf, " `sourcecodeid`=\"%s\" and `status` in (0,99)", sID.c_str());
	vector<DB::BuildRuleData> *pBuildRules = DB::BuildRule().query()->where(m_szBuf)->all();
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
				set_respond_back(HTTP_INTERNAL, "1", "BuildRule_DeployData failed", "");
				return;
			}

			conditions.clear();
			conditions.insert(pair<string, string>("guid", pBRDD->deployhostid));
			DB::Resource_HostData *pHD = DB::Resource_Host().query()->where(conditions)->first();
			if (!pHD)
			{
				set_respond_back(HTTP_INTERNAL, "1", "Resource_HostData failed", "");
				return;
			}


			// 整理输出数据
			Json::Value jsonPost;
			jsonPost["sourcecodeid"] = sID;
			jsonPost["buildruleid"] = brd.guid;
			jsonPost["localpath"] = pBRDD->deploypath;

			HttpClient http;
			http.post(pHD->address, pHD->port, sPath, Json::FastWriter().write(jsonPost));
		}
	}
	set_respond_back(HTTP_OK, "0", "create sourcecode resource success!", "");
}

void SourceCodeDeploy::background_process()
{

}