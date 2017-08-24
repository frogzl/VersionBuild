#include "AddBuildRuleResult.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/BuildResult.h"
AddBuildRuleResult::AddBuildRuleResult(ServiceData *pD) :m_pD(pD)
{
}

AddBuildRuleResult::~AddBuildRuleResult()
{
}

void AddBuildRuleResult::process_task()
{
	// 检查输入参数是否存在
	if (!check_inputdata())
	{
		DB::BuildResultData brd;
		brd.guid = getGUID();
		brd.build_rule_id = _sBuildRuleID;
		brd.version = _nVersion;
		brd.status = _nStatus;
		brd.log = _sLog;
		brd.storage_id = _sStorageID;
		if (DB::BuildResult().create(brd)->exec())
		{
			Json::Value jData;
			jData["source_code_id"] = brd.guid;
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

		}
		else
			m_pD->set_respond_back(499, "1", "add new Build Result failed.", "");
	}

}

bool AddBuildRuleResult::check_inputdata()
{
	// build_rule_id
	if (m_pD->request_data().jData["build_rule_id"].isString())
		_sBuildRuleID = m_pD->request_data().jData["build_rule_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "build_rule_id is empty.", "");
		return false;
	}

	// version
	if (m_pD->request_data().jData["version"].isString())
		_nVersion = m_pD->request_data().jData["version"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "version is empty.", "");
		return false;
	}

	// status
	if (m_pD->request_data().jData["status"].isInt())
		_nStatus = m_pD->request_data().jData["status"].asInt();
	else
	{
		m_pD->set_respond_back(499, "1", "status is empty.", "");
		return false;
	}

	// log
	if (m_pD->request_data().jData["log"].isString())
		_sLog = m_pD->request_data().jData["log"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "log is empty.", "");
		return false;
	}

	// storage_id
	if (m_pD->request_data().jData["storage_id"].isString())
		_sStorageID = m_pD->request_data().jData["storage_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "storage_id is empty.", "");
		return false;
	}
	return true;
}