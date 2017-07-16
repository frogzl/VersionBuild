#include "SourceCodeBuild.h"
#include "../Exception/HttpRequestException.h"
#include "../Tools/HttpClient.h"
#include "../Database/SourceCode_Deploy.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Deploy.h"
#include "../Database/Resource_SourceCode.h"
#include "../Database/Resource_Host.h"

SourceCodeBuild::SourceCodeBuild()
{
}

SourceCodeBuild::~SourceCodeBuild()
{
}

void SourceCodeBuild::process_task()
{
	// 检查输入参数是否存在
	string sFailedDetail;
	if (!check_inputdata(sFailedDetail))
	{
		set_respond_back(HTTP_BADREQUEST, "1", "param missing", sFailedDetail);
		return;
	}

	// 找到对应的sourcecode，通过clone_url
	DB::Conditions conditions;
	conditions.insert(pair<string, string>("clone_url", m_rdInData.jData["clone_url"].asString()));
	DB::Resource_SourceCodeData *pRSCD = DB::Resource_SourceCode().query()->where(conditions)->first();
	if (pRSCD)
	{
		conditions.clear();
		conditions.insert(pair<string, string>("sourcecodeid", pRSCD->guid));
		vector<DB::BuildRuleData> *pVecBuildRule = DB::BuildRule().query()->where(conditions)->all();
		if (pVecBuildRule)
		{
			string sPath = "/buildrule/build";
			for (int nIndex = 0; nIndex < pVecBuildRule->size(); nIndex++)
			{
				DB::BuildRuleData &buildruleData = (*pVecBuildRule)[nIndex];
				if (buildruleData.autobuild)
				{
					DB::Resource_HostData *pRHD = (DB::Resource_HostData *)get_buildrule_host(buildruleData.deployid);
					if (!pRHD)
						continue;

					Json::Value jsonPost;
					jsonPost["buildruleid"] = buildruleData.guid;

					HttpClient http;
					http.post(pRHD->address, pRHD->port, sPath, Json::FastWriter().write(jsonPost));
					delete pRHD;
				}
			}
			delete pVecBuildRule;
		}
		delete pRSCD;
	}
	else
	{
		set_respond_back(HTTP_BADREQUEST, "1", "no source code matched", "");
		return;
	}
	set_respond_back(HTTP_OK, "0", "successed", "");
}

void SourceCodeBuild::background_process()
{

}

bool SourceCodeBuild::check_inputdata(string &sFailedDetail)
{
	/*
	name
	head
	size
	clone_url
	*/
	if (m_rdInData.jData["name"].asString().compare("") == 0)
	{
		sFailedDetail = "name is missing";
		return false;
	}

	if (m_rdInData.jData["head"].asString().compare("") == 0)
	{
		sFailedDetail = "head is missing";
		return false;
	}

	if (m_rdInData.jData["clone_url"].asString().compare("") == 0)
	{
		sFailedDetail = "clone_url is missing";
		return false;
	}
	return true;
}

void* SourceCodeBuild::get_buildrule_host(string sDeployid)
{
	DB::Conditions con;
	con.insert(pair<string, string>("guid", sDeployid));
	DB::BuildRule_DeployData *pBRDD = DB::BuildRule_Deploy().query()->where(con)->first();
	if (pBRDD)
	{
		con.clear();
		con.insert(pair<string, string>("guid", pBRDD->deployhostid));
		DB::Resource_HostData *pRHD = DB::Resource_Host().query()->where(con)->first();
		delete pBRDD;
		return pRHD;
	}
	return NULL;
}