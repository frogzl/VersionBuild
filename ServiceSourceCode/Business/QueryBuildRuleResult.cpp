#include "QueryBuildRuleResult.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/BuildResult.h"
QueryBuildRuleResult::QueryBuildRuleResult(ServiceData *pD) :m_pD(pD)
{
}

QueryBuildRuleResult::~QueryBuildRuleResult()
{
}

void QueryBuildRuleResult::process_task()
{
	char szBuf[255];
	if (!check_inputdata())
	{
		DB::Conditions con;
		if (_sBuildResultID.compare("") != 0)
			con.insert(pair<string, string>("guid", _sBuildResultID));
		if (_sBuildRuleID.compare("") != 0)
			con.insert(pair<string, string>("build_rule_id", _sBuildRuleID));
		if (con.size() > 0)
		{
			vector<DB::BuildResultData> *pVecBRDD = DB::BuildResult().query()->where(con)->all();
			if (pVecBRDD)
			{
				int nCount = pVecBRDD->size();
				Json::Value jData;
				for (int nIndex = 0; nIndex < nCount; nIndex++)
				{
					Json::Value jItem;
					DB::BuildResultData &data = (*pVecBRDD)[nIndex];
					jItem["guid"] = data.guid;
					jItem["build_rule_id"] = data.build_rule_id;
					jItem["version"] = data.version;
					jItem["status"] = data.status;
					jItem["log"] = data.log;
					jItem["storage_id"] = data.storage_id;
					jData.append(jItem);
				}
				Json::Value jRespond;
				jRespond["data"] = jData;
				m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

				delete pVecBRDD;
			}
			else
			{
				sprintf(szBuf, "guid:%s, build_rule_id:%s", _sBuildResultID.c_str(), _sBuildRuleID.c_str());
				m_pD->set_respond_back(499, "1", szBuf, "");
			}
		}
		else
			m_pD->set_respond_back(499, "1", "Parameter is null strings.", "");
	}
}

bool QueryBuildRuleResult::check_inputdata()
{
	// source_code_id¡¢build_rule_idºÍbuild_result_id
	int nParamCnt = (int)m_pD->request_data().vecParameters.size();
	if (nParamCnt == 3)
	{
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
		_sBuildRuleID = m_pD->request_data().vecParameters[1];
		_sBuildResultID = m_pD->request_data().vecParameters[2];
	}
	else if (nParamCnt == 2)
	{
		_sSourceCodeID = m_pD->request_data().vecParameters[0];
		_sBuildRuleID = m_pD->request_data().vecParameters[1];
		_sBuildResultID = "";
	}
	else
	{
		m_pD->set_respond_back(499, "1", "Parameter is missing.", "");
		return false;
	}

	return true;
}