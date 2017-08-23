#include "QueryCompilingToolTemplate.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/CompilingTool.h"
#include <string>
using namespace std;
QueryCompilingToolTemplate::QueryCompilingToolTemplate(ServiceData *pD) :m_pD(pD)
{
}

QueryCompilingToolTemplate::~QueryCompilingToolTemplate()
{
}

void QueryCompilingToolTemplate::process_task()
{
	char szBuf[255];
	string sCompilingToolID = "";
	if (m_pD->request_data().vecParameters.size() == 1)
		sCompilingToolID = m_pD->request_data().vecParameters[0];

	if (sCompilingToolID.compare("") == 0)
	{
		vector<DB::CompilingToolData> *pVecCTD = DB::CompilingTool().query()->all();
		if (pVecCTD)
		{
			int nCount = pVecCTD->size();
			Json::Value jData;
			for (int nIndex = 0; nIndex < nCount; nIndex++)
			{
				Json::Value jItem;
				DB::CompilingToolData &data = (*pVecCTD)[nIndex];
				jItem["guid"] = data.guid;
				jItem["name"] = data.name;
				jItem["discription"] = data.discription;
				jItem["data_template"] = data.data_template;
				jItem["compile_cmd_template"] = data.compile_cmd_template;
				jData.append(jItem);
			}
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);
			delete pVecCTD;
		}
		else
		{
			m_pD->set_respond_back(499, "1", "no data is available.", "");
		}
	}
	else
	{
		sprintf(szBuf, "`guid`=\"%s\"", sCompilingToolID.c_str());
		DB::CompilingToolData *pCTD = DB::CompilingTool().query()->where(szBuf)->first();
		if (pCTD)
		{
			Json::Value jData;
			Json::Value jItem;
			jItem["guid"] = pCTD->name;
			jItem["name"] = pCTD->name;
			jItem["discription"] = pCTD->discription;
			jItem["data_template"] = pCTD->data_template;
			jItem["compile_cmd_template"] = pCTD->compile_cmd_template;
			jData.append(jItem);
			Json::Value jRespond;
			jRespond["data"] = jData;
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jRespond);

			delete pCTD;
		}
		else
		{
			sprintf(szBuf, "Compiling tool %s is not found", sCompilingToolID.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
		}
	}
}