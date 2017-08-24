#include "UpdateBuildRule.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
#include "../Database/BuildRule.h"
UpdateBuildRule::UpdateBuildRule(ServiceData *pD) :m_pD(pD)
{
}

UpdateBuildRule::~UpdateBuildRule()
{
}

void UpdateBuildRule::process_task()
{
	char szBuf[255] = { 0 };
	if (!check_inputdata())
	{
		set<string> setFilter;
		DB::BuildRuleData brd;
		if (m_pD->request_data().jData["source_code_id"].isString())
		{
			setFilter.insert("source_code_id");
			brd.source_code_id = m_pD->request_data().jData["source_code_id"].asString();
		}
		if (m_pD->request_data().jData["inner_id"].isString())
		{
			setFilter.insert("inner_id");
			brd.inner_id = m_pD->request_data().jData["inner_id"].asString();
		}
		if (m_pD->request_data().jData["status"].isString())
		{
			setFilter.insert("status");
			brd.status = m_pD->request_data().jData["status"].asString();
		}
		if (m_pD->request_data().jData["auto_build"].isInt())
		{
			setFilter.insert("auto_build");
			brd.auto_build = m_pD->request_data().jData["auto_build"].asString();
		}
		if (m_pD->request_data().jData["proxy_host_id"].isString())
		{
			setFilter.insert("proxy_host_id");
			brd.proxy_host_id = m_pD->request_data().jData["proxy_host_id"].asString();
		}
		if (m_pD->request_data().jData["server_host_id"].isString())
		{
			setFilter.insert("server_host_id");
			brd.server_host_id = m_pD->request_data().jData["server_host_id"].asString();
		}
		if (m_pD->request_data().jData["task_id"].isString())
		{
			setFilter.insert("task_id");
			brd.task_id = m_pD->request_data().jData["task_id"].asString();
		}
		if (m_pD->request_data().jData["target_file_name"].isString())
		{
			setFilter.insert("target_file_name");
			brd.target_file_name = m_pD->request_data().jData["target_file_name"].asString();
		}
		if (m_pD->request_data().jData["target_file_path"].isString())
		{
			setFilter.insert("target_file_path");
			brd.target_file_path = m_pD->request_data().jData["target_file_path"].asString();
		}
		if (m_pD->request_data().jData["compile_tool_ins_id"].isString())
		{
			setFilter.insert("compile_tool_ins_id");
			brd.compile_tool_ins_id = m_pD->request_data().jData["compile_tool_ins_id"].asString();
		}
		if (m_pD->request_data().jData["output_directory_template"].isString())
		{
			setFilter.insert("output_directory_template");
			brd.compile_tool_ins_id = m_pD->request_data().jData["output_directory_template"].asString();
		}

		sprintf(szBuf, "`guid`='%s'", _sBuildRuleID.c_str());
		if (DB::BuildRule().update(setFilter, brd)->where(szBuf)->exec())
		{
			Json::Value jData;
			jData["build_rule_id"] = _sBuildRuleID;
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

		}
		else
			m_pD->set_respond_back(499, "1", "update build rule failed.", "");
	}
}

bool UpdateBuildRule::check_inputdata()
{
	// source_code_idºÍbuild_rule_id
	int nParamCnt = (int)m_pD->request_data().vecParameters.size();
	if (nParamCnt == 2)
	{
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
		_sBuildRuleID = m_pD->request_data().vecParameters[1];
	}
	else
	{
		m_pD->set_respond_back(499, "1", "Parameter is missing.", "");
		return false;
	}
	return true;
}