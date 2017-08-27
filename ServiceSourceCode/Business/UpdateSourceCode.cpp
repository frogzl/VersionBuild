#include "UpdateSourceCode.h"
#include "../Exception/HttpRequestException.h"
#include "../Tools/HttpClient.h"
#include "../Database/SourceCode.h"
UpdateSourceCode::UpdateSourceCode(ServiceData *pD) :m_pD(pD)
{
}

UpdateSourceCode::~UpdateSourceCode()
{
}

void UpdateSourceCode::process_task()
{
	// 检查输入参数是否存在
	char szBuf[255] = { 0 };
	if (!check_inputdata())
	{
		set<string> setFilter;
		DB::SourceCodeData scd;
		if (m_pD->request_data().jData["name"].isString())
		{
			setFilter.insert("name");
			scd.name = m_pD->request_data().jData["name"].asString();
		}

		if (m_pD->request_data().jData["discription"].isString())
		{
			setFilter.insert("discription");
			scd.discription = m_pD->request_data().jData["discription"].asString();
		}

		if (m_pD->request_data().jData["version_control_id"].isString())
		{
			setFilter.insert("version_control_id");
			scd.version_control_ins_id = m_pD->request_data().jData["version_control_ins_id"].asString();
		}

		if (m_pD->request_data().jData["start_version"].isInt())
		{
			setFilter.insert("start_version");
			scd.start_version = m_pD->request_data().jData["start_version"].asInt();
		}

		if (m_pD->request_data().jData["current_version"].isInt())
		{
			setFilter.insert("current_version");
			scd.current_version = m_pD->request_data().jData["current_version"].asInt();
		}

		if (m_pD->request_data().jData["status"].isInt())
		{
			setFilter.insert("status");
			scd.status = m_pD->request_data().jData["status"].asInt();
		}

		if (m_pD->request_data().jData["build_state"].isInt())
		{
			setFilter.insert("build_state");
			scd.build_state = m_pD->request_data().jData["build_state"].asInt();
		}

		if (m_pD->request_data().jData["build_state_mask"].isInt())
		{
			setFilter.insert("build_state_mask");
			scd.build_state_mask = m_pD->request_data().jData["build_state_mask"].asInt();
		}

		sprintf(szBuf, "`guid`='%s'", _sSourceCodeID.c_str());
		if (DB::SourceCode().update(setFilter, scd)->where(szBuf)->exec())
		{
			Json::Value jData;
			jData["source_code_id"] = _sSourceCodeID;
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

		}
		else
			m_pD->set_respond_back(499, "1", "update Source Code failed.", "");
	}
}

bool UpdateSourceCode::check_inputdata()
{
	int nParamCnt = (int)m_pD->request_data().vecParameters.size();
	if (nParamCnt == 1)
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
	else
	{
		m_pD->set_respond_back(499, "1", "Parameter is missing.", "");
		return false;
	}
	return true;
}