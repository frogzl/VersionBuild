#include "SourceCodeCreate.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Database/Resource_SourceCode.h"
#include "../../Database/BuildRule.h"
#include "../../Database/BuildRule_Deploy.h"
#include "../../Database/BuildRule_Depend.h"

namespace B
{
	SourceCodeCreate::SourceCodeCreate(Controller::Controller *pController) :SourceCodeBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
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
		dbSourceCodeData.repertoryname = m_inputData["repertoryname"].asString();
		string sTmp = m_inputData["branchname"].asString();
		g2u(sTmp.c_str(), sTmp.length(), m_szBuf, Buffer_Size);
		dbSourceCodeData.branchname = m_szBuf;
		sTmp = m_inputData["name"].asString();
		g2u(sTmp.c_str(), sTmp.length(), m_szBuf, Buffer_Size);
		dbSourceCodeData.name = m_szBuf;
		sTmp = m_inputData["description"].asString();
		g2u(sTmp.c_str(), sTmp.length(), m_szBuf, Buffer_Size);
		dbSourceCodeData.discription = m_szBuf;
		dbSourceCodeData.startversion = m_inputData["versionstart"].asInt();
		dbSourceCodeData.currentversion = dbSourceCodeData.startversion;
		dbSourceCodeData.status = m_inputData["status"].asInt();
		dbSourceCodeData.buildstate = m_inputData["buildstate"].asInt();
		dbSourceCodeData.buildstatemask = m_inputData["buildstatemask"].asInt();
		if (!dbSourceCode.create(dbSourceCodeData)->exec())
		{
			set_respond_back(HTTP_INTERNAL, "1", "create sourcecode failed", "");
			return;
		}
		jsonRespondData["guid"] = dbSourceCodeData.guid;

		Json::Value jsonBuildRules = m_inputData["buildrules"];
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
				set_respond_back(HTTP_INTERNAL, "1", "create buildrule_deploy failed", "");
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
				set_respond_back(HTTP_INTERNAL, "1", "create buildrule failed", "");
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
					set_respond_back(HTTP_INTERNAL, "1", "create buildrule_depend failed", "");
					return;
				}
				Json::Value jsonRespondDepend;
				jsonRespondDepend["guid"] = dbBuildRuleDependData.guid;
				jsonRespondDepends.append(jsonRespondDeploy);
			}
			jsonRespondBuildRule["depends"] = jsonRespondDepends;
			jsonRespondData["buildrules"].append(jsonRespondBuildRule);
		}

		set_respond_back(HTTP_OK, "0", "create sourcecode resource success!", "", jsonRespondData);
	}

	void SourceCodeCreate::background_process()
	{

	}
}