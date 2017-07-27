#include "SourceCodeQuery.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/Resource_SourceCode.h"

SourceCodeQuery::SourceCodeQuery(ServiceData *pD) :m_pD(pD)
{
}

SourceCodeQuery::~SourceCodeQuery()
{
}

void SourceCodeQuery::process_task()
{
	DB::Resource_SourceCode dbSourceCode;
	vector<DB::Resource_SourceCodeData> *pVecSourceCodeDatas = NULL;
	if (m_pD->request_data().mConditions["sourcecodeid"].compare("") == 0)
	{
		pVecSourceCodeDatas = dbSourceCode.query()->all();
	}
	else
	{
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", m_pD->request_data().mConditions["sourcecodeid"]));
		pVecSourceCodeDatas = dbSourceCode.query()->where(conditions)->all();
	}

	Json::Value jsonData;
	if (pVecSourceCodeDatas)
	{
		for (int nIndexSourceCodeData = 0; nIndexSourceCodeData < (*pVecSourceCodeDatas).size(); nIndexSourceCodeData++)
		{
			Json::Value jsonSourceCodeData;
			jsonSourceCodeData["guid"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].guid;
			jsonSourceCodeData["repertoryname"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].repertoryname;
			jsonSourceCodeData["branchname"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].branchname;
			jsonSourceCodeData["name"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].name;
			jsonSourceCodeData["discription"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].discription;
			jsonSourceCodeData["startversion"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].startversion;
			jsonSourceCodeData["currentversion"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].currentversion;
			jsonSourceCodeData["status"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].status;
			jsonSourceCodeData["buildstate"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].buildstate;
			jsonSourceCodeData["buildstatemask"] = (*pVecSourceCodeDatas)[nIndexSourceCodeData].buildstatemask;

			jsonData.append(jsonSourceCodeData);
		}
		delete pVecSourceCodeDatas;
	}
	m_pD->set_respond_back(HTTP_OK, "0", "successed", "", jsonData);
}