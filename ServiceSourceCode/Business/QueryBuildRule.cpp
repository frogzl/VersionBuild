#include "QueryBuildRule.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/BuildRule.h"
QueryBuildRule::QueryBuildRule(ServiceData *pD) :m_pD(pD)
{
}

QueryBuildRule::~QueryBuildRule()
{
}

void QueryBuildRule::process_task()
{
	char szBuf[255];
	if (!check_inputdata())
	{
		DB::Conditions con;
		if (_sBuildRuleID.compare("") != 0)
			con.insert(pair<string, string>("guid", _sBuildRuleID));
		if (_sSourceCodeID.compare("") != 0)
			con.insert(pair<string, string>("source_code_id", _sSourceCodeID));
		if (con.size() > 0)
		{
			vector<DB::BuildRuleData> *pVecBRD = DB::BuildRule().query()->where(con)->all();
			if (pVecBRD)
			{
				int nCount = pVecBRD->size();
				Json::Value jData;
				for (int nIndex = 0; nIndex < nCount; nIndex++)
				{
					Json::Value jItem;
					DB::BuildRuleData &data = (*pVecBRD)[nIndex];
					jItem["guid"] = data.guid;
					jItem["source_code_id"] = data.source_code_id;
					jItem["inner_id"] = data.inner_id;
					jItem["status"] = data.status;
					jItem["auto_build"] = data.auto_build;
					jItem["proxy_host_id"] = data.proxy_host_id;
					jItem["server_host_id"] = data.server_host_id;
					jItem["task_id"] = data.task_id;
					jItem["target_file_name"] = data.target_file_name;
					jItem["target_file_path"] = data.target_file_path;
					jItem["compile_tool_ins_id"] = data.compile_tool_ins_id;
					jItem["output_directory_template"] = data.output_directory_template;
					jData.append(jItem);
				}
				Json::Value jRespond;
				jRespond["data"] = jData;
				m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

				delete pVecBRD;
			}
			else
			{
				sprintf(szBuf, "guid:%s, source_code_id:%s", _sBuildRuleID.c_str(), _sSourceCodeID.c_str());
				m_pD->set_respond_back(499, "1", szBuf, "");
			}
		}
		else
			m_pD->set_respond_back(499, "1", "Parameter is null strings.", "");
	}
}

bool QueryBuildRule::check_inputdata()
{
	// source_code_idºÍbuild_rule_id
	int nParamCnt = (int)m_pD->request_data().vecParameters.size();
	if (nParamCnt == 2)
	{
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
		_sBuildRuleID = m_pD->request_data().vecParameters[1];
	}
	else if (nParamCnt == 1)
	{
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
		_sBuildRuleID = "";
	}
	else
	{
		m_pD->set_respond_back(499, "1", "Parameter is missing.", "");
		return false;
	}

	return true;
}