#include "ResourceQuery.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Database/Resource.h"
namespace B
{
	ResourceQuery::ResourceQuery(Controller::Controller *pController) :ResourceBusiness(pController)
	{
	}

	ResourceQuery::~ResourceQuery()
	{
	}

	void ResourceQuery::process_task()
	{
		char szBuf[255];
		string sConditions = "";
		if (input_parameters()["id"].compare("") != 0)
		{
			sprintf(szBuf, "`guid`=\"%s\" ", input_parameters()["id"].c_str());
			sConditions += szBuf;
		}
		if (input_parameters()["type"].compare("") != 0)
		{
			sprintf(szBuf, "`type`=%s ", input_parameters()["type"].c_str());
			if (sConditions.length() > 0)
				sConditions += "and ";
			sConditions += szBuf;
		}

		vector<DB::ResourceData> *pVecRD = NULL;
		if (sConditions.length() > 0)
			pVecRD = DB::Resource().query()->where(sConditions)->all();
		else
			pVecRD = DB::Resource().query()->all();

		Json::Value jsonData;
		if (pVecRD)
		{
			for (int nIndexData = 0; nIndexData < (*pVecRD).size(); nIndexData++)
			{
				Json::Value jsonResourceData;
				jsonResourceData["guid"] = (*pVecRD)[nIndexData].guid;
				jsonResourceData["name"] = (*pVecRD)[nIndexData].name;
				jsonResourceData["discription"] = (*pVecRD)[nIndexData].discription;
				jsonResourceData["type"] = (*pVecRD)[nIndexData].type;
				jsonResourceData["resourceid"] = (*pVecRD)[nIndexData].resourceid;

				jsonData.append(jsonResourceData);
			}
			delete pVecRD;
		}
		set_respond_back(HTTP_OK, "0", "successed", "", jsonData);

	}

	void ResourceQuery::background_process()
	{

	}
}