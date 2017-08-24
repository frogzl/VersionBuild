#include "AddBuildRuleDepends.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/BuildRule_Depend.h"
AddBuildRuleDepends::AddBuildRuleDepends(ServiceData *pD) :m_pD(pD)
{
}

AddBuildRuleDepends::~AddBuildRuleDepends()
{
}

void AddBuildRuleDepends::process_task()
{
	// 检查输入参数是否存在
	if (!check_inputdata())
	{
		DB::BuildRule_DependData brdd;
		brdd.guid = getGUID();
		brdd.build_rule_id = _sBuildRuleID;
		brdd.depend_source_code_id = _sDependSourceCodeID;
		brdd.depend_build_rule_id = _sDependBuildRuleID;
		brdd.depend_build_result_id = _sDependBuildResultID;
		brdd.depend_usage_mode = _sDependUsageMode;
		if (DB::BuildRule_Depend().create(brdd)->exec())
		{
			Json::Value jData;
			jData["source_code_id"] = brdd.guid;
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

		}
		else
			m_pD->set_respond_back(499, "1", "add new Build Rule Depends failed.", "");
	}

}

bool AddBuildRuleDepends::check_inputdata()
{
	// build_rule_id
	if (m_pD->request_data().jData["build_rule_id"].isString())
		_sBuildRuleID = m_pD->request_data().jData["build_rule_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "build_rule_id is empty.", "");
		return false;
	}

	// depend_source_code_id
	if (m_pD->request_data().jData["depend_source_code_id"].isString())
		_sDependSourceCodeID = m_pD->request_data().jData["depend_source_code_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "depend_source_code_id is empty.", "");
		return false;
	}

	// depend_build_rule_id
	if (m_pD->request_data().jData["depend_build_rule_id"].isString())
		_sDependBuildRuleID = m_pD->request_data().jData["depend_build_rule_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "depend_build_rule_id is empty.", "");
		return false;
	}

	// depend_build_result_id
	if (m_pD->request_data().jData["depend_build_result_id"].isString())
		_sDependBuildResultID = m_pD->request_data().jData["depend_build_result_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "depend_build_result_id is empty.", "");
		return false;
	}

	// depend_usage_mode
	if (m_pD->request_data().jData["depend_usage_mode"].isString())
		_sDependUsageMode = m_pD->request_data().jData["depend_usage_mode"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "depend_usage_mode is empty.", "");
		return false;
	}
	return true;
}