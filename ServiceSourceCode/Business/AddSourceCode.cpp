#include "AddSourceCode.h"
#include "../Exception/HttpRequestException.h"
#include "../Tools/HttpClient.h"
#include "../Database/SourceCode.h"
AddSourceCode::AddSourceCode(ServiceData *pD) :m_pD(pD)
{
}

AddSourceCode::~AddSourceCode()
{
}

void AddSourceCode::process_task()
{
	// 检查输入参数是否存在
	if (!check_inputdata())
	{
		DB::SourceCodeData scd;
		scd.guid = getGUID();
		scd.name = _sName;
		scd.discription = _sDiscription;
		scd.version_control_id = _sVersionControlID;
		scd.start_version = _nStartVersion;
		scd.current_version = _nStartVersion;
		scd.status = 0;
		scd.build_state = _nBuildState;
		scd.build_state_mask = 0;
		scd.version = 0;
		if (DB::SourceCode().create(scd)->exec())
		{
			Json::Value jData;
			jData["source_code_id"] = scd.guid;
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

		}
		else
			m_pD->set_respond_back(499, "1", "add new source code failed.", "");
	}

}

bool AddSourceCode::check_inputdata()
{
	// 名称
	if (m_pD->request_data().jData["name"].isString())
		_sName = m_pD->request_data().jData["name"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "name is empty.", "");
		return false;
	}

	// discription
	if (m_pD->request_data().jData["discription"].isString())
		_sDiscription = m_pD->request_data().jData["discription"].asString();
	else
		_sDiscription = "";

	// version_control_id
	if (m_pD->request_data().jData["version_control_id"].isString())
		_sVersionControlID = m_pD->request_data().jData["version_control_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "version_control_id is empty.", "");
		return false;
	}

	// start_version
	if (m_pD->request_data().jData["start_version"].isInt())
		_nStartVersion = m_pD->request_data().jData["start_version"].isInt();
	else
		_nStartVersion = 0;

	// build_state
	if (m_pD->request_data().jData["build_state"].isInt())
		_nBuildState = m_pD->request_data().jData["build_state"].asInt();
	else
	{
		m_pD->set_respond_back(499, "1", "build_state is empty.", "");
		return false;
	}

	return true;
}