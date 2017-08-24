#include "BuildSourceCode.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
#include "../Database/SourceCode.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Depend.h"
#include "../Database/BuildResult.h"
BuildSourceCode::BuildSourceCode(ServiceData *pD) :m_pD(pD)
{
}

BuildSourceCode::~BuildSourceCode()
{
}

/*
{
"deploy_commands":"",
"update_commands":"",
"target":{
"file_name":"",
"file_path":"",
"output_directory_template":""
},
"depends":[
{"storage_id":"","alias":""},
{"storage_id":"","alias":""},
{"storage_id":"","alias":""},
{"storage_id":"","alias":""}
]
}
*/
void BuildSourceCode::process_task(ENState enState)
{
	// 检查输入参数是否存在
	char szBuf[255] = { 0 };
	if (!check_inputdata())
	{
		if (lock_source_code())
		{
			sprintf(szBuf, "`guid`='%s'", _sSourceCodeID.c_str());
			DB::SourceCodeData *pSCD = DB::SourceCode().query()->where(szBuf)->first();
			if (pSCD)
			{
				delete pSCD;
			}
			else
			{
				m_pD->set_respond_back(499, "4", "this source code don't found.", "");
				return;
			}
			if (enState == enAutoBuild)
				sprintf(szBuf, "`source_code_id`=\"%s\" and `auto_build`=1", _sSourceCodeID.c_str());
			else
				sprintf(szBuf, "`source_code_id`=\"%s\"", _sSourceCodeID.c_str());

			vector<DB::BuildRuleData> *pVecBRD = DB::BuildRule().query()->where(szBuf)->all();
			if (pVecBRD)
			{
				int nBRCnt = pVecBRD->size();
				for (int nIndexBR = 0; nIndexBR < nBRCnt; nIndexBR++)
				{
					DB::BuildRuleData &data = (*pVecBRD)[nIndexBR];
					sprintf(szBuf, "`build_rule_id`=\"%s\"", data.guid.c_str());
					vector<DB::BuildRule_DependData> *pVecBRDD = DB::BuildRule_Depend().query("depend_build_result_id")->where(szBuf)->all();
					if (pVecBRDD)
					{
						string sStorageIDs = "";
						int nBRDDCnt = pVecBRDD->size();
						for (int nIndexBRDD = 0; nIndexBRDD < nBRDDCnt; nIndexBRDD++)
						{
							if (nIndexBRDD != nBRDDCnt - 1)
								sStorageIDs += ("'" + (*pVecBRDD)[nIndexBRDD].depend_build_result_id + "',");
							else
								sStorageIDs += ("'" + (*pVecBRDD)[nIndexBRDD].depend_build_result_id + "'");
						}
						delete pVecBRDD;

						sprintf(szBuf, "`guid` in (%s)", sStorageIDs.c_str());
						vector<DB::BuildResultData> *pVecBResultD = DB::BuildResult().query("storage_id")->where(szBuf)->all();
						if (pVecBResultD)
						{
							Json::Value jDepends;
							int nBResultCnt = pVecBResultD->size();
							for (int nIndexBResult = 0; nIndexBResult < nBResultCnt; nIndexBResult++)
							{
								Json::Value jStorage;
								jStorage["storage_id"] = (*pVecBResultD)[nIndexBResult].storage_id;
								jDepends.append(jStorage);
							}
							delete pVecBResultD;
						}
						else
						{
							m_pD->set_respond_back(499, "6", "failed to find build rule depends.", "");
							break;
						}
					}
				}
				delete pVecBRD;
			}
			else
			{
				m_pD->set_respond_back(499, "5", "this source code don't have build rule which you want.", "");
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