#include "HostQuery.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Database/Resource_Host.h"
namespace B
{

	HostQuery::HostQuery(Controller::Controller *pController) :HostBusiness(pController)
	{
	}


	HostQuery::~HostQuery()
	{
	}

	void HostQuery::process_task()
	{
		string sCondition = "";
		if (input_parameters()["hostid"].compare("") != 0)
			sCondition += ("guid=\"" + input_parameters()["hostid"] + "\"");
		if (input_parameters()["type"].compare("") != 0)
			sCondition += ("type=" + input_parameters()["type"] );
		
		vector<DB::Resource_HostData> *pData = NULL;
		DB::Resource_Host dbHost;
		if (sCondition.compare("") == 0)
			pData = dbHost.query()->all();
		else
			pData = dbHost.query()->where(sCondition)->all();

		if (pData)
		{
			Json::Value jsonRespond;
			for (int nIndex = 0; nIndex < pData->size(); nIndex++)
			{
				DB::Resource_HostData &data = (*pData)[nIndex];
				Json::Value jsonHost;
				jsonHost["guid"] = data.guid;
				jsonHost["name"] = data.name;
				jsonHost["discription"] = data.discription;
				jsonHost["type"] = data.type;
				jsonHost["address"] = data.address;
				jsonHost["port"] = data.port;
				jsonHost["operatingsystem"] = data.operatingsystem;
				jsonHost["cpu"] = data.cpu;
				jsonHost["memory"] = data.memory;
				jsonHost["storage"] = data.storage;
				jsonHost["environmentvariable"] = data.environmentvariable;

				jsonRespond.append(jsonHost);
			}
			set_respond_back(HTTP_OK, "0", "successed", "", jsonRespond);
		}
		set_respond_back(HTTP_OK, "0", "successed", "");
	}

	void HostQuery::background_process()
	{

	}
}