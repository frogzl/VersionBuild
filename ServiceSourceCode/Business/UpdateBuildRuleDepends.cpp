#include "UpdateBuildRuleDepends.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/BuildRule_Depend.h"
#include "../Common.h"
UpdateBuildRuleDepends::UpdateBuildRuleDepends(ServiceData *pD) :m_pD(pD)
{
}

UpdateBuildRuleDepends::~UpdateBuildRuleDepends()
{
}

void UpdateBuildRuleDepends::process_task()
{
	// 检查输入参数是否存在
	char szBuf[255] = { 0 };
	if (!check_inputdata())
	{
		set<string> setFilter;
		DB::BuildRule_DependData brdd;
		if (m_pD->request_data().jData["build_rule_id"].isString())
		{
			setFilter.insert("build_rule_id");
			brdd.build_rule_id = m_pD->request_data().jData["build_rule_id"].asString();
		}

		if (m_pD->request_data().jData["depend_source_code_id"].isString())
		{
			setFilter.insert("depend_source_code_id");
			brdd.depend_source_code_id = m_pD->request_data().jData["depend_source_code_id"].asString();
		}

		if (m_pD->request_data().jData["depend_build_rule_id"].isString())
		{
			setFilter.insert("depend_build_rule_id");
			brdd.depend_build_rule_id = m_pD->request_data().jData["depend_build_rule_id"].asString();
		}

		if (m_pD->request_data().jData["depend_build_result_id"].isString())
		{
			setFilter.insert("depend_build_result_id");
			brdd.depend_build_result_id = m_pD->request_data().jData["depend_build_result_id"].asString();
		}

		if (m_pD->request_data().jData["depend_usage_mode"].isString())
		{
			setFilter.insert("depend_usage_mode");
			brdd.depend_build_result_id = m_pD->request_data().jData["depend_usage_mode"].asString();
		}

		sprintf(szBuf, "`guid`='%s'", _sBuildRuleDependID.c_str());
		if (DB::BuildRule_Depend().update(setFilter, brdd)->where(szBuf)->exec())
		{
			Json::Value jData;
			jData["build_rule_depend_id"] = _sBuildRuleDependID;
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

		}
		else
			m_pD->set_respond_back(499, "1", "update build rule depend failed.", "");
	}

}

bool UpdateBuildRuleDepends::check_inputdata()
{
	// source_code_id、build_rule_id和build_result_id
	int nParamCnt = (int)m_pD->request_data().vecParameters.size();
	if (nParamCnt == 3)
	{
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
		_sBuildRuleID = m_pD->request_data().vecParameters[1];
		_sBuildRuleDependID = m_pD->request_data().vecParameters[2];
	}
	else
	{
		m_pD->set_respond_back(499, "1", "Parameter is missing.", "");
		return false;
	}	return true;
}