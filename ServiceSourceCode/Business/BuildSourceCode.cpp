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
"unique_id":"7d11f0f8-ab96-4532-b5a7-4b8d9191e436",
"version":"1",
"task_path":"/7d11f0f8-ab96-4532-b5a7-4b8d9191e436/1/sourcecode/build",
"plugin_deploy_id":"",
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
],
"finish_url":"/source-code/{id}/build-rule/{id}/build-result"
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
			Json::Value jTaskRequest;
			jTaskRequest["task_path"] = "/7d11f0f8-ab96-4532-b5a7-4b8d9191e436/1/sourcecode/build";
			jTaskRequest["plugin_deploy_id"] = _sPluginDeployID;
			sprintf(szBuf, "`guid`='%s'", _sSourceCodeID.c_str());
			DB::SourceCodeData *pSCD = DB::SourceCode().query()->where(szBuf)->first();
			if (pSCD)
			{
				Json::Value jRespond;
				Network::Request_Data rd;
				sprintf(szBuf, "/version-control-instance/{%s}", pSCD->version_control_ins_id.c_str());
				delete pSCD;

				if (Network::get(Network::enReverseProxy, 
					"33ff9e34-a9a3-4d42-a84c-8ecea956354f", 
					"1", 
					szBuf, 
					rd, 
					cb_get_version_control_ins, 
					&jRespond))
				{
					jTaskRequest["update_commands"] = jRespond["update_commands"].asString();
				}
				else
				{
					m_pD->set_respond_back(499, "7", "version-control-instance don't found.", "");
					return;
				}
			}
			else
			{
				m_pD->set_respond_back(499, "4", "this source code don't found.", "");
				return;
			}

			bool bRet = true;
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
					Json::Value jTarget;
					jTarget["file_name"] = data.target_file_name;
					jTarget["file_path"] = data.target_file_path;
					jTarget["output_directory_template"] = data.output_directory_template;
					jTaskRequest["target"] = jTarget;

					sprintf(szBuf, "/source-code/{%s}/build-rule/{%s}/build-result", _sSourceCodeID.c_str(), data.guid.c_str());
					jTaskRequest["finish_url"] = szBuf;

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
							jTaskRequest["depends"] = jDepends;
							delete pVecBResultD;
							// 发起任务
							Network::Request_Data rd;
							rd.sData = Json::FastWriter().write(jTaskRequest);
							DB::BuildRuleData tmp;
							if (Network::post(Network::enReverseProxy, "ffeafe48-3c6e-49d8-a85c-783167eada00", "1", "/task", rd, cb_create_task, &(tmp.task_id)))
							{
								set<string> setFilter;
								setFilter.insert("task_id");
								sprintf(szBuf, "`guid`='%s'", data.guid.c_str());
								if (!DB::BuildRule().update(setFilter, tmp)->where(szBuf)->exec())
								{
									sprintf(szBuf, "build rule %s update task_id to %s failed.", tmp.task_id.c_str());
									m_pD->set_respond_back(499, "6", "create task failed.", "");
									bRet = false;
									break;
								}
							}
							else
							{
								sprintf(szBuf, "build rule %s create task failed.", data.guid.c_str());
								m_pD->set_respond_back(499, "6", "create task failed.", "");
								bRet = false;
								break;
							}
						}
						else
						{
							m_pD->set_respond_back(499, "6", "failed to find build rule depends.", "");
							bRet = false;
							break;
						}

					}
				}
				if (bRet)
					m_pD->set_respond_back(HTTP_OK, "0", "successed", "");
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

	// 任务部署ID
	if (m_pD->request_data().jData["plugin_deploy_id"].isString())
		_sPluginDeployID = m_pD->request_data().jData["plugin_deploy_id"].asString();
	else
	{
		m_pD->set_respond_back(499, "1", "plugin_deploy_id is empty.", "");
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
		scd.build_state = 0;
		scd.version = pSCD->version + 1;
		set<string> setFilter;
		setFilter.insert("status");
		setFilter.insert("version");
		setFilter.insert("build_state");
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

bool BuildSourceCode::cb_get_version_control_ins(Helper::Network::Respond_Data *pData, void*pArg)
{
	Json::Value *pValue = (Json::Value *)pArg;
	Json::Reader reader;
	if (!reader.parse(pData->sData.c_str(), *pValue))
		return false;
	if (pData->nHttpStatus != 200)
		return false;
	return true;
}

bool BuildSourceCode::cb_create_task(Network::Respond_Data *pData, void*pArg)
{
	string &sTaskID = *(string*)pArg;
	Json::Value jValue;
	Json::Reader reader;
	if (!reader.parse(pData->sData.c_str(), jValue))
		return false;
	sTaskID = jValue["task_id"].asString();
	if (pData->nHttpStatus != 200)
		return false;
	return true;
}