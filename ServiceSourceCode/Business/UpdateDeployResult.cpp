#include "UpdateDeployResult.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/SourceCode.h"
UpdateDeployResult::UpdateDeployResult(ServiceData *pD) :m_pD(pD)
{
}

UpdateDeployResult::~UpdateDeployResult()
{
}

void UpdateDeployResult::process_task()
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

bool UpdateDeployResult::check_inputdata()
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