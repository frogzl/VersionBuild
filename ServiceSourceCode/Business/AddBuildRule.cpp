#include "AddBuildRule.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
#include "../Database/BuildRule.h"
AddBuildRule::AddBuildRule(ServiceData *pD) :m_pD(pD)
{
}

AddBuildRule::~AddBuildRule()
{
}

void AddBuildRule::process_task()
{
	if (!check_inputdata())
	{
		DB::BuildRuleData brd;
		brd.guid = getGUID();
		brd.source_code_id = _sSourceCodeID;
		brd.inner_id = _nInnerID;
		brd.status = 0;
		brd.auto_build = _nAutoBuild;
		brd.proxy_host_id = _sProxyHostID;
		brd.server_host_id = _sServerHostID;
		brd.task_id = "";
		brd.target_file_name = _sTargetFileName;
		brd.target_file_path = _sTargetFilePath;
		brd.compile_tool_ins_id = _sCompileToolInsID;
		brd.output_directory_template = _sOutputDirectoryTemplate;
		if (DB::BuildRule().create(brd)->exec())
		{
			Json::Value jData;
			jData["build_rule_id"] = brd.guid;
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

		}
		else
			m_pD->set_respond_back(499, "1", "add new build rule failed.", "");
	}
}

bool AddBuildRule::check_inputdata()
{
	// source code id
	if (m_pD->request_data().vecParameters.size() == 1)
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
	else
	{
		m_pD->set_respond_back(499, "1", "source code id is empty.", "");
		return false;
	}

	// inner_id
	if (m_pD->request_data().jData["inner_id"].isInt())
		_nInnerID = m_pD->request_data().jData["inner_id"].asInt();
	else
	{
		m_pD->set_respond_back(499, "1", "inner_id is empty.", "");
		return false;
	}

	// auto_build
	if (m_pD->request_data().jData["auto_build"].isInt())
		_nAutoBuild = m_pD->request_data().jData["auto_build"].asInt();
	else
		_nAutoBuild = 0;

	// proxy_host_id
	if (m_pD->request_data().jData["proxy_host_id"].isString())
		_sProxyHostID = m_pD->request_data().jData["proxy_host_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "proxy_host_id is empty.", "");
		return false;
	}

	// server_host_id
	if (m_pD->request_data().jData["server_host_id"].isString())
		_sServerHostID = m_pD->request_data().jData["server_host_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "server_host_id is empty.", "");
		return false;
	}

	// target_file_name
	if (m_pD->request_data().jData["target_file_name"].isString())
		_sTargetFileName = m_pD->request_data().jData["target_file_name"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "target_file_name is empty.", "");
		return false;
	}

	// target_file_path
	if (m_pD->request_data().jData["target_file_path"].isString())
		_sTargetFilePath = m_pD->request_data().jData["target_file_path"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "target_file_path is empty.", "");
		return false;
	}

	// compile_tool_ins_id
	if (m_pD->request_data().jData["compile_tool_ins_id"].isString())
		_sCompileToolInsID = m_pD->request_data().jData["compile_tool_ins_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "compile_tool_ins_id is empty.", "");
		return false;
	}

	// output_directory_template
	if (m_pD->request_data().jData["output_directory_template"].isString())
		_sOutputDirectoryTemplate = m_pD->request_data().jData["output_directory_template"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "output_directory_template is empty.", "");
		return false;
	}
	return true;
}