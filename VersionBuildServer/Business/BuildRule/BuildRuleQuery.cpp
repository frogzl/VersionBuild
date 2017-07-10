#include <vector>
#include "BuildRuleQuery.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Database/BuildRule.h"
namespace B
{
	BuildRuleQuery::BuildRuleQuery(Controller::Controller *pController) :BuildRuleBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}

	BuildRuleQuery::~BuildRuleQuery()
	{
	}

	void BuildRuleQuery::process_task()
	{
		DB::BuildRule dbBuildRule;
		vector<DB::BuildRuleData> *pVecBuildRuleDatas = NULL;
		if (input_parameters()["buildid"].compare("") != 0)
		{
			DB::Conditions conditions;
			conditions.insert(pair<string, string>("guid", input_parameters()["buildruleid"]));
			pVecBuildRuleDatas = dbBuildRule.query()->where(conditions)->all();
		}
		else if (input_parameters()["sourcecodeid"].compare("") != 0)
		{
			DB::Conditions conditions;
			conditions.insert(pair<string, string>("sourcecodeid", input_parameters()["sourcecodeid"]));
			pVecBuildRuleDatas = dbBuildRule.query()->where(conditions)->all();
		}
		else
		{
			pVecBuildRuleDatas = dbBuildRule.query()->all();
		}

		Json::Value jsonData;
		if (pVecBuildRuleDatas)
		{
			for (int nIndexSourceCodeData = 0; nIndexSourceCodeData < (*pVecBuildRuleDatas).size(); nIndexSourceCodeData++)
			{
				Json::Value jsonSourceCodeData;
				jsonSourceCodeData["guid"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].guid;
				jsonSourceCodeData["sourcecodeid"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].sourcecodeid;
				jsonSourceCodeData["innerid"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].innerid;
				jsonSourceCodeData["autobuild"] = (int)(*pVecBuildRuleDatas)[nIndexSourceCodeData].autobuild;
				jsonSourceCodeData["platform"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].platform;
				jsonSourceCodeData["deployid"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].deployid;
				jsonSourceCodeData["buildcmd"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].buildcmd;
				jsonSourceCodeData["targetfiletype"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].targetfiletype;
				jsonSourceCodeData["targetfilename"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].targetfilename;
				jsonSourceCodeData["targetfilepath"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].targetfilepath;
				jsonSourceCodeData["logfilename"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].logfilename;
				jsonSourceCodeData["logfilepath"] = (*pVecBuildRuleDatas)[nIndexSourceCodeData].logfilepath;

				jsonData.append(jsonData);
			}
			delete pVecBuildRuleDatas;
		}
		set_respond_back(HTTP_OK, "0", "successed", "", jsonData);
	}

	void BuildRuleQuery::background_process()
	{

	}
}