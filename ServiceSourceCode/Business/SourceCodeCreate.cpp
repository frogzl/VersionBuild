#include "SourceCodeCreate.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
SourceCodeCreate::SourceCodeCreate(BusinessInterface *pB) :m_pB(pB)
{
}

SourceCodeCreate::~SourceCodeCreate()
{
}

/* 创建源码资源
* 1、创建Resource_SourceCodes记录
* 2、创建BuildRule_Deploys记录
* 3、创建BuildRules记录
* 4、创建BuildRule_Depends记录
* 输入格式：
{
sourcecode:{
url:xx,
branchname:xx,
discription:xx,
startversion:1,
currentversion:1,
status:0,
buildstate:0x2312,
buildstatemask:0x2312
},
buildrules:[
{
innerid:xx,
autobuild:true,
platform:xx,
buildcmd:xx,
targetfiletype:xx,
targetfilename:xx,
targetfilepath:xx,
logfilename:xx,
logfilepath:xx,
deployhost:{
id:xx,
path:xx
},
depends:[
{
dependsourcecodeid:xx,
dependbuildruleid:xx,
dependbuildresultid:xx,
dependusagemode:xx
},
...,
{
dependsourcecodeid:xx,
dependbuildruleid:xx,
dependbuildresultid:xx,
dependusagemode:xx
}
]
}
]
}

* 输出格式：
{
sourcecode:{
guid:xx
},
buildrules:[
{
guid:xx
deploy:{
guid:xx
},
depends:[
{
guid:xx
},
...,
{
guid:xx
}
]
}
]
}
*/
void SourceCodeCreate::process_task()
{
	Json::Value jsonRespondData;

	// 1、创建Resource_SourceCodes记录
	DB::Resource_SourceCode dbSourceCode;
	DB::Resource_SourceCodeData dbSourceCodeData;
	dbSourceCodeData.guid = getGUID();
	dbSourceCodeData.repertoryname = m_pB->request_data().jData["repertoryname"].asString();
	string sTmp = m_pB->request_data().jData["branchname"].asString();
	char *szBranchNameBuf = new char[sTmp.length() * 3 + 1];
	g2u(sTmp.c_str(), sTmp.length(), szBranchNameBuf, sTmp.length() * 3 + 1);
	dbSourceCodeData.branchname = szBranchNameBuf;
	delete [] szBranchNameBuf;

	sTmp = m_pB->request_data().jData["name"].asString();
	char *szNameBuf = new char[sTmp.length() * 3 + 1];
	g2u(sTmp.c_str(), sTmp.length(), szNameBuf, sTmp.length() * 3 + 1);
	dbSourceCodeData.name = szNameBuf;
	delete [] szNameBuf;

	sTmp = m_pB->request_data().jData["description"].asString();
	char *szDescriptionBuf = new char[sTmp.length() * 3 + 1];
	g2u(sTmp.c_str(), sTmp.length(), szDescriptionBuf, sTmp.length() * 3 + 1);
	dbSourceCodeData.discription = szDescriptionBuf;
	delete [] szDescriptionBuf;

	dbSourceCodeData.startversion = m_pB->request_data().jData["versionstart"].asInt();
	dbSourceCodeData.currentversion = dbSourceCodeData.startversion;
	dbSourceCodeData.status = m_pB->request_data().jData["status"].asInt();
	dbSourceCodeData.buildstate = m_pB->request_data().jData["buildstate"].asInt();
	dbSourceCodeData.buildstatemask = m_pB->request_data().jData["buildstatemask"].asInt();
	if (!dbSourceCode.create(dbSourceCodeData)->exec())
	{
		m_pB->set_respond_back(HTTP_INTERNAL, "1", "create sourcecode failed", "");
		return;
	}
	jsonRespondData["guid"] = dbSourceCodeData.guid;

	Json::Value jsonBuildRules = m_pB->request_data().jData["buildrules"];
	for (int nIndexBuildRule = 0; nIndexBuildRule < jsonBuildRules.size(); nIndexBuildRule++)
	{
		Json::Value jsonBuildRule = jsonBuildRules[nIndexBuildRule];
		Json::Value jsonDeploy = jsonBuildRule["deployhost"];
		Json::Value jsonDepends = jsonBuildRule["depends"];

		// 2、创建BuildRule_Deploys记录
		DB::BuildRule_Deploy dbBuildRuleDeploy;
		DB::BuildRule_DeployData dbBuildRuleDeployData;
		dbBuildRuleDeployData.guid = getGUID();
		dbBuildRuleDeployData.deployhostid = jsonDeploy["id"].asString();
		dbBuildRuleDeployData.deploypath = jsonDeploy["path"].asString();
		if (!dbBuildRuleDeploy.create(dbBuildRuleDeployData)->exec())
		{
			m_pB->set_respond_back(HTTP_INTERNAL, "1", "create buildrule_deploy failed", "");
			return;
		}
		Json::Value jsonRespondDeploy;
		jsonRespondDeploy["guid"] = dbBuildRuleDeployData.guid;

		// 3、创建BuildRules记录
		DB::BuildRule dbBuildRule;
		DB::BuildRuleData dbBuildRuleData;
		dbBuildRuleData.guid = getGUID();
		dbBuildRuleData.sourcecodeid = dbSourceCodeData.guid;
		dbBuildRuleData.innerid = jsonBuildRule["innerid"].asInt();
		dbBuildRuleData.autobuild = jsonBuildRule["autucompile"].asBool();
		dbBuildRuleData.platform = jsonBuildRule["compileplatform"].asString();
		dbBuildRuleData.buildcmd = jsonBuildRule["compilecmd"].asString();
		dbBuildRuleData.targetfiletype = jsonBuildRule["compileoutputtype"].asInt();
		dbBuildRuleData.targetfilename = jsonBuildRule["compileoutput"].asString();
		dbBuildRuleData.targetfilepath = jsonBuildRule["compileoutputdir"].asString();
		dbBuildRuleData.logfilename = jsonBuildRule["compilelog"].asString();
		dbBuildRuleData.logfilepath = jsonBuildRule["compilelogdir"].asString();
		dbBuildRuleData.deployid = dbBuildRuleDeployData.guid;
		dbBuildRuleData.status = 0;
		if (!dbBuildRule.create(dbBuildRuleData)->exec())
		{
			m_pB->set_respond_back(HTTP_INTERNAL, "1", "create buildrule failed", "");
			return;
		}
		Json::Value jsonRespondBuildRule;

		jsonRespondBuildRule["guid"] = dbBuildRuleData.guid;
		jsonRespondBuildRule["deploy"] = jsonRespondDeploy;

		//  4、创建BuildRule_Depends记录	
		Json::Value jsonRespondDepends;
		for (int nIndexDepend = 0; nIndexDepend < jsonDepends.size(); nIndexDepend++)
		{
			Json::Value jsonDepend = jsonDepends[nIndexDepend];
			DB::BuildRule_Depend dbBuildRuleDepend;
			DB::BuildRule_DependData dbBuildRuleDependData;
			dbBuildRuleDependData.guid = getGUID();
			dbBuildRuleDependData.buildruleid = dbBuildRuleData.guid;
			dbBuildRuleDependData.dependsourcecodeid = jsonDepend["dependsourcecodeid"].asString();
			dbBuildRuleDependData.dependbuildruleid = jsonDepend["dependbuildruleid"].asString();
			dbBuildRuleDependData.dependbuildresultid = jsonDepend["dependbuildresultid"].asString();
			dbBuildRuleDependData.dependusagemode = jsonDepend["dependusagemode"].asInt();
			if (!dbBuildRuleDepend.create(dbBuildRuleDependData)->exec())
			{
				m_pB->set_respond_back(HTTP_INTERNAL, "1", "create buildrule_depend failed", "");
				return;
			}
			Json::Value jsonRespondDepend;
			jsonRespondDepend["guid"] = dbBuildRuleDependData.guid;
			jsonRespondDepends.append(jsonRespondDeploy);
		}
		jsonRespondBuildRule["depends"] = jsonRespondDepends;
		jsonRespondData["buildrules"].append(jsonRespondBuildRule);
	}

	m_pB->set_respond_back(HTTP_OK, "0", "create sourcecode resource success!", "", jsonRespondData);
}
