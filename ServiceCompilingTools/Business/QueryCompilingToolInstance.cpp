#include "QueryCompilingToolInstance.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/CompilingToolInstance.h"
#include <sstream>
using namespace std;
QueryCompilingToolInstance::QueryCompilingToolInstance(ServiceData *pD) :m_pD(pD)
{
}


QueryCompilingToolInstance::~QueryCompilingToolInstance()
{
}

void QueryCompilingToolInstance::process_task()
{
	char szBuf[255];
	string sCompilingToolInsID = "";
	if (m_pD->request_data().vecParameters.size() == 1)
		sCompilingToolInsID = m_pD->request_data().vecParameters[0];

	if (sCompilingToolInsID.compare("") == 0)
	{
		vector<DB::CompilingToolInstanceData> *pVecCTID = DB::CompilingToolInstance().query()->all();
		if (pVecCTID)
		{
			int nCount = pVecCTID->size();
			Json::Value jData;
			for (int nIndex = 0; nIndex < nCount; nIndex++)
			{
				Json::Value jItem;
				DB::CompilingToolInstanceData &data = (*pVecCTID)[nIndex];
				jItem["guid"] = data.guid;
				jItem["compiling_tool_id"] = data.compiling_tool_id;
				jItem["data"] = data.data;
				jItem["compile_cmd"] = data.compile_cmd;
				jData.append(jItem);
			}
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);
			delete pVecCTID;
		}
		else
		{
			m_pD->set_respond_back(499, "1", "no data is available.", "");
		}
	}
	else
	{
		sprintf(szBuf, "`guid`=\"%s\"", sCompilingToolInsID.c_str());
		DB::CompilingToolInstanceData *pCTID = DB::CompilingToolInstance().query()->where(szBuf)->first();
		if (pCTID)
		{
			Json::Value jData;
			Json::Value jItem;
			jItem["guid"] = pCTID->guid;
			jItem["compiling_tool_id"] = pCTID->compiling_tool_id;
			jItem["data"] = pCTID->data;
			jItem["compile_cmd"] = pCTID->compile_cmd;
			jData.append(jItem);
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

			delete pCTID;
		}
		else
		{
			sprintf(szBuf, "Compiling tool %s is not found", sCompilingToolInsID.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
		}
	}

}
