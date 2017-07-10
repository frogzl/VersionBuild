#include "BuildRuleDeploy.h"
#include <vector>
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Tools/HttpClient.h"
#include "../../Database/BuildRule.h"
#include "../../Database/BuildRule_Depend.h"
#include "../../Database/BuildResult.h"
#include "../../Database/Resource_SourceCode.h"
#include "../../Database/SourceCode_Deploy.h"
#include "../../Database/Resource_Host.h"
#include "../../Database/Storage.h"
namespace B
{
	BuildRuleDeploy::BuildRuleDeploy(Controller::Controller *pController) :BuildRuleBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}

	BuildRuleDeploy::~BuildRuleDeploy()
	{
	}

	/*
	 * 1°¢clone ‘¥¬Î
	 * 2°¢ªÒ»°“¿¿µ
	 */
	void BuildRuleDeploy::process_task()
	{
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", m_inputData["sourcecodeid"].asString()));
		DB::Resource_SourceCodeData *pRSCD = DB::Resource_SourceCode().query()->where(conditions)->first();
		if (!pRSCD)
		{
			set_respond_back(HTTP_INTERNAL, "1", "Resource_SourceCodeData failed", "");
			return;
		}

		conditions.clear();
		conditions.insert(pair<string, string>("guid", pRSCD->deployid));
		DB::SourceCode_DeployData *pSCDD = DB::SourceCode_Deploy().query()->where(conditions)->first();
		if (!pSCDD)
		{
			set_respond_back(HTTP_INTERNAL, "1", "SourceCode_DeployData failed", "");
			return;
		}

		conditions.clear();
		conditions.insert(pair<string, string>("guid", pSCDD->deployhostid));
		DB::Resource_HostData *pRHD = DB::Resource_Host().query()->where(conditions)->first();
		if (!pRHD)
		{
			set_respond_back(HTTP_INTERNAL, "1", "Resource_HostData failed", "");
			return;
		}

		// clone 
		char szURL[255];
		sprintf(szURL, "git clone https://%s:%d/r/%s", pRHD->address.c_str(), pRHD->port, pRSCD->repertoryname.c_str());
		string sCmd = szURL;
		string sErrorMsg = "";
		if (!process_command(sCmd, sErrorMsg, m_inputData["localpath"].asString().c_str()))
		{
			set_respond_back(HTTP_INTERNAL, "1", "process clone command failed", "");
			return;
		}

		// “¿¿µ
		conditions.clear();
		conditions.insert(pair<string, string>("buildruleid", m_inputData["buildruleid"].asString()));
		vector<DB::BuildRule_DependData> *pBRDDs = DB::BuildRule_Depend().query()->where(conditions)->all();
		if (pBRDDs)
		{
			for (int nIndex = 0; nIndex < pBRDDs->size(); nIndex++)
			{
				DB::BuildRule_DependData &brdd = (*pBRDDs)[nIndex];
				string sSourceCodeName = get_sourcecode_name(brdd.dependsourcecodeid);
				string sDependPath = m_inputData["localpath"].asString() + "\\depend\\" + sSourceCodeName;
				init_depend_data_to_local(brdd.dependbuildresultid, sDependPath);
			}
		}
		set_respond_back(HTTP_OK, "0", "successed", "");
	}

	void BuildRuleDeploy::background_process()
	{

	}

	string BuildRuleDeploy::get_sourcecode_name(string &sData)
	{
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", sData));
		DB::Resource_SourceCodeData *pRSCD = DB::Resource_SourceCode().query()->where(conditions)->first();
		if (pRSCD)
		{
			return pRSCD->name;
		}
		return "";
	}

	void BuildRuleDeploy::init_depend_data_to_local(string &sDependResultID, string &sStoragePath)
	{
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", sDependResultID));
		DB::BuildResultData *pBRD = DB::BuildResult().query()->where(conditions)->first();
		if (pBRD)
		{
			conditions.clear();
			conditions.insert(pair<string, string>("guid", pBRD->storageid));
			DB::StorageData *pSD = DB::Storage().query()->where(conditions)->first();
			if (pSD)
			{
				HttpClient http;
				http.download_file(pSD->storagehostlist, sStoragePath);
			}
		}
	}
}