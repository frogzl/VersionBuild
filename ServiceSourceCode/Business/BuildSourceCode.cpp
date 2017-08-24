#include "BuildSourceCode.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
#include "../Database/SourceCode.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Depend.h"
BuildSourceCode::BuildSourceCode(ServiceData *pD) :m_pD(pD)
{
}

BuildSourceCode::~BuildSourceCode()
{
}

void BuildSourceCode::process_task(ENState enState)
{
	// 检查输入参数是否存在
	char szBuf[255] = { 0 };
	if (!check_inputdata())
	{
		if (lock_source_code())
		{
			if (enState == enAutoBuild)
				sprintf(szBuf, "`source_code_id`=\"%s\" and `auto_build`=1", _sSourceCodeID.c_str());
			else
				sprintf(szBuf, "`source_code_id`=\"%s\"", _sSourceCodeID.c_str());

			vector<DB::BuildRuleData> *pVecBRD = DB::BuildRule().query()->where(szBuf)->all();
			if (pVecBRD)
			{

				delete pVecBRD;
			}
			else
			{
				m_pD->set_respond_back(499, "4", "this source code don't have build rule which you want.", "");
			}
		}
	}
}

bool BuildSourceCode::check_inputdata()
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

bool BuildSourceCode::lock_source_code()
{
	bool bRet = false;
	char szBuf[255] = { 0 };
	sprintf(szBuf, "`guid`=\"%s\" and `status`=2", _sSourceCodeID.c_str());
	DB::SourceCodeData *pSCD = DB::SourceCode().query()->where(szBuf)->first();
	if (pSCD)
	{
		DB::SourceCodeData scd;
		scd.status = 2;
		scd.version = pSCD->version + 1;
		set<string> setFilter;
		setFilter.insert("status");
		setFilter.insert("version");
		sprintf(szBuf, "`guid`=\"%s\" and `status`=2 and `version`=%d", _sSourceCodeID.c_str(), pSCD->version);
		if (DB::SourceCode().update(setFilter, scd)->where(szBuf)->exec())
			bRet = true;
		else
			m_pD->set_respond_back(499, "3", "update status failed,maybe status is already changed.", "");
		delete pSCD;
	}
	else
		m_pD->set_respond_back(499, "2", "Can't find source code in status completed.", "");
	return bRet;
}