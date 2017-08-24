#include "QuerySourceCode.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/SourceCode.h"
QuerySourceCode::QuerySourceCode(ServiceData *pD) :m_pD(pD)
{
}

QuerySourceCode::~QuerySourceCode()
{
}

void QuerySourceCode::process_task()
{
	char szBuf[255];
	if (!check_inputdata())
	{
		DB::Conditions con;
		if (_sSourceCodeID.compare("") != 0)
			con.insert(pair<string, string>("guid", _sSourceCodeID));
		if (con.size() > 0)
		{
			vector<DB::SourceCodeData> *pVecBRDD = DB::SourceCode().query()->where(con)->all();
			if (pVecBRDD)
			{
				int nCount = pVecBRDD->size();
				Json::Value jData;
				for (int nIndex = 0; nIndex < nCount; nIndex++)
				{
					Json::Value jItem;
					DB::SourceCodeData &data = (*pVecBRDD)[nIndex];
					jItem["guid"] = data.guid;
					jItem["name"] = data.name;
					jItem["discription "] = data.discription;
					jItem["version_control_id"] = data.version_control_id;
					jItem["start_version"] = data.start_version;
					jItem["current_version"] = data.current_version;
					jItem["status"] = data.status;
					jItem["build_state"] = data.build_state;
					jItem["build_state_mask"] = data.build_state_mask;
					jItem["version"] = data.version;
					jData.append(jItem);
				}
				Json::Value jRespond;
				jRespond["data"] = jData;
				m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

				delete pVecBRDD;
			}
			else
			{
				sprintf(szBuf, "guid:%s", _sSourceCodeID.c_str());
				m_pD->set_respond_back(499, "1", szBuf, "");
			}
		}
		else
			m_pD->set_respond_back(499, "1", "Parameter is null strings.", "");
	}
}

bool QuerySourceCode::check_inputdata()
{
	// source_code_id¡¢build_rule_idºÍbuild_result_id
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