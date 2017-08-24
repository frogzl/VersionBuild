#include "UpdateBuildRuleResult.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/BuildResult.h"
#include "../Common.h"
UpdateBuildRuleResult::UpdateBuildRuleResult(ServiceData *pD) :m_pD(pD)
{
}

UpdateBuildRuleResult::~UpdateBuildRuleResult()
{
}

void UpdateBuildRuleResult::process_task()
{
	// 检查输入参数是否存在
	char szBuf[255] = { 0 };
	if (!check_inputdata())
	{
		set<string> setFilter;
		DB::BuildResultData brd;
		if (m_pD->request_data().jData["build_rule_id"].isString())
		{
			setFilter.insert("build_rule_id");
			brd.build_rule_id = m_pD->request_data().jData["build_rule_id"].asString();
		}

		if (m_pD->request_data().jData["version"].isInt())
		{
			setFilter.insert("version");
			brd.version = m_pD->request_data().jData["version"].asInt();
		}

		if (m_pD->request_data().jData["status"].isInt())
		{
			setFilter.insert("status");
			brd.status = m_pD->request_data().jData["status"].asInt();
		}

		if (m_pD->request_data().jData["log"].isString())
		{
			setFilter.insert("log");
			brd.log = m_pD->request_data().jData["log"].asString();
		}

		if (m_pD->request_data().jData["storage_id"].isString())
		{
			setFilter.insert("storage_id");
			brd.storage_id = m_pD->request_data().jData["storage_id"].asString();
		}

		sprintf(szBuf, "`guid`='%s'", _sBuildResultID.c_str());
		if (DB::BuildResult().update(setFilter, brd)->where(szBuf)->exec())
		{
			Json::Value jData;
			jData["build_result_id"] = _sBuildResultID;
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

		}
		else
			m_pD->set_respond_back(499, "1", "update BuildResult failed.", "");
	}
}

bool UpdateBuildRuleResult::check_inputdata()
{
	int nParamCnt = (int)m_pD->request_data().vecParameters.size();
	if (nParamCnt == 3)
	{
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
		_sBuildRuleID = m_pD->request_data().vecParameters[1];
		_sBuildResultID = m_pD->request_data().vecParameters[2];
	}
	else
	{
		m_pD->set_respond_back(499, "1", "Parameter is missing.", "");
		return false;
	}

	return true;
}