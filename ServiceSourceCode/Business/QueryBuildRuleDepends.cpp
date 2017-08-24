#include "QueryBuildRuleDepends.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/BuildRule_Depend.h"
QueryBuildRuleDepends::QueryBuildRuleDepends(ServiceData *pD) :m_pD(pD)
{
}

QueryBuildRuleDepends::~QueryBuildRuleDepends()
{
}

void QueryBuildRuleDepends::process_task()
{
	char szBuf[255];
	if (!check_inputdata())
	{
		DB::Conditions con;
		if (_sBuildRuleDependID.compare("") != 0)
			con.insert(pair<string, string>("guid", _sBuildRuleDependID));
		if (_sBuildRuleID.compare("") != 0)
			con.insert(pair<string, string>("build_rule_id", _sBuildRuleID));
		if (con.size() > 0)
		{
			vector<DB::BuildRule_DependData> *pVecBRDD = DB::BuildRule_Depend().query()->where(con)->all();
			if (pVecBRDD)
			{
				int nCount = pVecBRDD->size();
				Json::Value jData;
				for (int nIndex = 0; nIndex < nCount; nIndex++)
				{
					Json::Value jItem;
					DB::BuildRule_DependData &data = (*pVecBRDD)[nIndex];
					jItem["guid"] = data.guid;
					jItem["build_rule_id"] = data.build_rule_id;
					jItem["depend_source_code_id"] = data.depend_source_code_id;
					jItem["depend_build_rule_id"] = data.depend_build_rule_id;
					jItem["depend_build_result_id"] = data.depend_build_result_id;
					jItem["depend_usage_mode"] = data.depend_usage_mode;
					jData.append(jItem);
				}
				Json::Value jRespond;
				jRespond["data"] = jData;
				m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

				delete pVecBRDD;
			}
			else
			{
				sprintf(szBuf, "guid:%s, build_rule_id:%s", _sBuildRuleDependID.c_str(), _sBuildRuleID.c_str());
				m_pD->set_respond_back(499, "1", szBuf, "");
			}
		}
		else
			m_pD->set_respond_back(499, "1", "Parameter is null strings.", "");
	}
}

bool QueryBuildRuleDepends::check_inputdata()
{
	// source_code_id¡¢build_rule_idºÍbuild_result_id
	int nParamCnt = (int)m_pD->request_data().vecParameters.size();
	if (nParamCnt == 3)
	{
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
		_sBuildRuleID = m_pD->request_data().vecParameters[1];
		_sBuildRuleDependID = m_pD->request_data().vecParameters[2];
	}
	else if (nParamCnt == 2)
	{
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
		_sBuildRuleID = m_pD->request_data().vecParameters[1];
		_sBuildRuleDependID = "";
	}
	else
	{
		m_pD->set_respond_back(499, "1", "Parameter is missing.", "");
		return false;
	}

	return true;
}