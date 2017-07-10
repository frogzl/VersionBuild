#pragma once
#include "../BuildRuleBusiness.h"
#include "../../Common.h"
#include "../../Database/Resource_SourceCode.h"
#include "../../Database/BuildRule.h"
#include "../../Database/BuildRule_Deploy.h"
#include "../../Database/BuildRule_Depend.h"
#include "../../Database/BuildResult.h"
#include "../../Database/Storage.h"
#include "../../Database/Resource_Host.h"
	namespace B
{
	class BuildRuleBuild : public BuildRuleBusiness
	{
	public:
		BuildRuleBuild(Controller::Controller *pController);
		~BuildRuleBuild();

		void process_task();
		void background_process();
	private:
		bool get_buildrule(DB::BuildRuleData *&pDBBuildRuleData);

		bool get_deploy(string &sDeployId, DB::BuildRule_DeployData *&pDBBuildRuleDeployData);

		bool update_depends(DB::BuildRule_DeployData *pDBBuildRuleDeployData, DB::BuildRuleData *&pDBBuildRuleData);
		bool get_depends(string &sBuildRuleId, vector<DB::BuildRule_DependData> *&pDBBuildRuleDependDatas);
		bool update_depend(DB::BuildRule_DeployData *pDBBuildRuleDeployData, DB::BuildRule_DependData &dbBuildRuleDependData);
		bool get_depend_build_result_version(string &sBuildResultId, DB::BuildResultData *&pDBBuildResultData);
		bool get_depend_build_result_latest_version(string &sBuildRuleId, DB::BuildResultData *&pDBBuildResultData);
		bool get_depend_fileinfo(DB::BuildRule_DeployData *pDBBuildRuleDeployData, DB::BuildRule_DependData &dbBuildRuleDependData, string &fileName, string &filePath);
		bool refresh_depend_file(string &sStorageId, string sFileAbsolutePath);

		bool update_self(string &sWorkPath);

		bool analysis_logs(DB::BuildRuleData *pDBBuildRuleData, DB::BuildRule_DeployData *pDBBuildRuleDeployData, string &sWorkPath);
		bool is_build_successed(string &sWorkPath, DB::BuildRuleData *pDBBuildRuleData);
		bool get_deploy_fileinfo(DB::Resource_SourceCodeData *pDBSourceCodeData, DB::BuildRuleData *pDBBuildRuleData, DB::BuildRule_DeployData *pDBBuildRuleDeployData, string &sFileName, string &sFilePath);
		bool upload_file(string &sStorageId, string sFileName, string sFileAbsolutePath);

		bool end_task(DB::BuildRuleData *pDBBuildRuleData);
	};
}