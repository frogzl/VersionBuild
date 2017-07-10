#include "SourceCodeQuery.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Database/Resource_SourceCode.h"
namespace B
{
	SourceCodeQuery::SourceCodeQuery(Controller::Controller *pController) :SourceCodeBusiness(pController)
	{
	}

	SourceCodeQuery::~SourceCodeQuery()
	{
	}

	void SourceCodeQuery::process_task()
	{
		DB::Resource_SourceCode dbSourceCode;
		vector<DB::Resource_SourceCodeData> *pVecSourceCodeDatas = NULL;
		if (input_parameters()["sourcecodeid"].compare("") == 0)
		{
			pVecSourceCodeDatas = dbSourceCode.query()->all();
		}
		else
		{
			DB::Conditions conditions;
			conditions.insert(pair<string, string>("guid", input_parameters()["sourcecodeid"]));
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
		set_respond_back(HTTP_OK, "0", "successed", "", jsonData);
	}

	void SourceCodeQuery::background_process()
	{

	}
}