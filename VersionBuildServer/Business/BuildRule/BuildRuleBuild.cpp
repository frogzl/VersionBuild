#include "BuildRuleBuild.h"
#include <algorithm>
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Tools/HttpClient.h"
#include <Shellapi.h>
namespace B
{
	BuildRuleBuild::BuildRuleBuild(Controller::Controller *pController) :BuildRuleBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}

	BuildRuleBuild::~BuildRuleBuild()
	{
	}

	/* 构建
	* 1、更新依赖
	* 2、执行构建命令
	* 3、分析输出日志
	* 4、如果成功则根据targetfiletype处理构建结果，并存储
	* 5、更新sourcecodeid对应的buildstate（如果buildstate与buildstatemask相同，则还要更新status为2）
	* 输入格式：
	{
		buildruleid:xx
	}
	*/
	void BuildRuleBuild::process_task()
	{
		string sErrorMsg = "";
		DB::BuildRuleData *pDBBuildRuleData = NULL;
		DB::BuildRule_DeployData *pDBBuildRuleDeployData = NULL;

		// 获取buildrule数据
		if (!get_buildrule(pDBBuildRuleData))
		{
			set_respond_back(HTTP_INTERNAL, "1", "get buildrule failed", "");
			return;
		}

		// 获取部署位置
		if (!get_deploy(pDBBuildRuleData->deployid, pDBBuildRuleDeployData))
		{
			set_respond_back(HTTP_INTERNAL, "1", "get buildrule_deploy failed", "");
			return;
		}

		//更新所有依赖
		if (!update_depends(pDBBuildRuleDeployData, pDBBuildRuleData))
		{
			set_respond_back(HTTP_INTERNAL, "1", "update buildrule_depend files failed", "");
			return;
		}

		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", pDBBuildRuleData->sourcecodeid));
		DB::Resource_SourceCodeData *pDBSourceCode = DB::Resource_SourceCode().query()->where(conditions)->first();
		if (!pDBSourceCode)
		{
			set_respond_back(HTTP_INTERNAL, "1", "get Resource_SourceCodeData failed", "");
			return;
		}

		string sWorkPath = pDBBuildRuleDeployData->deploypath + "\\" + pDBSourceCode->branchname;
		// 更新自己
		if (!update_self(sWorkPath))
		{
			set_respond_back(HTTP_INTERNAL, "1", "update buildrule_depend files failed", "");
			return;
		}

		// 执行构建命令
		SHELLEXECUTEINFOA si;
		ZeroMemory(&si, sizeof(si));
		si.cbSize = sizeof(si);
		si.fMask = SEE_MASK_NOCLOSEPROCESS;
		si.lpVerb = "open";
		si.lpFile = pDBBuildRuleData->buildcmd.c_str();
		si.nShow = SW_SHOWNORMAL;
		si.lpDirectory = sWorkPath.c_str();
		ShellExecuteExA(&si);

		DWORD dwExitCode;
		GetExitCodeProcess(si.hProcess, &dwExitCode);
		while (dwExitCode == STILL_ACTIVE)
		{
			Sleep((DWORD)5);
			GetExitCodeProcess(si.hProcess, &dwExitCode);
		}
		CloseHandle(si.hProcess);


		// 分析输出日志
		if (!analysis_logs(pDBBuildRuleData, pDBBuildRuleDeployData, sWorkPath))
		{
			set_respond_back(HTTP_INTERNAL, "1", "analysis logs failed", "");
			return;
		}
		 
		// 更新sourcecodeid对应的buildstate（如果buildstate与buildstatemask相同，则还要更新status为2）
		if (!end_task(pDBBuildRuleData))
		{

		}
		set_respond_back(HTTP_OK, "0", "successed", "");
	}

	void BuildRuleBuild::background_process()
	{

	}

	///////////////////////////////// private /////////////////////////////////////////
	bool BuildRuleBuild::get_buildrule(DB::BuildRuleData *&pDBBuildRuleData)
	{
		DB::BuildRule dbBuildRule;
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", m_inputData["buildruleid"].asString()));
		pDBBuildRuleData = dbBuildRule.query()->where(conditions)->first();
		if (pDBBuildRuleData)
			return true;
		else
			return false;
	}

	bool BuildRuleBuild::get_deploy(string &sDeployId, DB::BuildRule_DeployData *&pDBBuildRuleDeployData)
	{
		DB::BuildRule_Deploy dbBuildRuleDeploy;
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", sDeployId));
		pDBBuildRuleDeployData = dbBuildRuleDeploy.query()->where(conditions)->first();
		if (pDBBuildRuleDeployData)
			return true;
		else
			return false;
	}

	bool BuildRuleBuild::update_depends(DB::BuildRule_DeployData *pDBBuildRuleDeployData, DB::BuildRuleData *&pDBBuildRuleData)
	{
		vector<DB::BuildRule_DependData> *pDBBuildRuleDependDatas = NULL;
		if (get_depends(pDBBuildRuleData->guid, pDBBuildRuleDependDatas))
		{
			int nSize = pDBBuildRuleDependDatas->size();
			for (int nIndexDependData = 0; nIndexDependData < nSize; nIndexDependData++)
				if (!update_depend(pDBBuildRuleDeployData, (*pDBBuildRuleDependDatas)[nIndexDependData]))
				{
					delete pDBBuildRuleDependDatas;
					return false;
				}
			delete pDBBuildRuleDependDatas;
		}
		return true;
	}

	bool BuildRuleBuild::get_depends(string &sBuildRuleId, vector<DB::BuildRule_DependData> *&pDBBuildRuleDependDatas)
	{
		DB::BuildRule_Depend dbBuildRuleDepend;
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("buildruleid", sBuildRuleId));
		pDBBuildRuleDependDatas = dbBuildRuleDepend.query()->where(conditions)->all();
		if (pDBBuildRuleDependDatas)
			return true;
		else
			return false;
	}

	bool BuildRuleBuild::update_depend(DB::BuildRule_DeployData *pDBBuildRuleDeployData, DB::BuildRule_DependData &dbBuildRuleDependData)
	{
		DB::BuildResultData *pDBCurrentBuildResultData = NULL;
		DB::BuildResultData *pDBLatestBuildResultData = NULL;
		if (get_depend_build_result_version(dbBuildRuleDependData.dependbuildresultid, pDBCurrentBuildResultData))
		{
			if (get_depend_build_result_latest_version(dbBuildRuleDependData.dependbuildruleid, pDBLatestBuildResultData))
			{
				if (pDBLatestBuildResultData->version != pDBCurrentBuildResultData->version)
				{
					string sFileName, sFilePath;
					if (get_depend_fileinfo(pDBBuildRuleDeployData, dbBuildRuleDependData, sFileName, sFilePath) )
						if (!refresh_depend_file(pDBLatestBuildResultData->storageid, sFilePath + sFileName))
						{
							delete pDBCurrentBuildResultData;
							delete pDBLatestBuildResultData;
							return false;
						}
				}
				delete pDBLatestBuildResultData;
			}
			else// 不存在依赖的版本，此时应该清理本地环境，刷新该条BuildRule_Depend 
			{
				delete pDBCurrentBuildResultData;
				return false;
			}
		}
		else
			return false;

		delete pDBLatestBuildResultData;
		delete pDBCurrentBuildResultData;
		return true;
	}

	bool BuildRuleBuild::get_depend_build_result_version(string &sBuildResultId, DB::BuildResultData *&pDBBuildResultData)
	{
		DB::BuildResult dbCurrentBuildResult;
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", sBuildResultId));
		pDBBuildResultData = dbCurrentBuildResult.query()->where(conditions)->first();
		if (pDBBuildResultData)
			return true;
		else
			return false;
	}

	bool BuildRuleBuild::get_depend_build_result_latest_version(string &sBuildRuleId, DB::BuildResultData *&pDBBuildResultData)
	{
		DB::BuildResult dbLatestBuildResult;
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("buildruleid", sBuildRuleId));
		pDBBuildResultData = dbLatestBuildResult.query()->where(conditions)->order_by("version DESC")->first();
		if (pDBBuildResultData)
			return true;
		else
			return false;
	}

	bool BuildRuleBuild::get_depend_fileinfo(DB::BuildRule_DeployData *pDBBuildRuleDeployData, DB::BuildRule_DependData &dbBuildRuleDependData, string &sFileName, string &sFilePath)
	{
		DB::Resource_SourceCode dbSourceCode;
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", dbBuildRuleDependData.dependsourcecodeid));
		DB::Resource_SourceCodeData *pDBSourceCode = dbSourceCode.query()->where(conditions)->first();
		if (pDBSourceCode)
		{
			DB::BuildRule dbBuildRuleDepend;
			conditions.clear();
			conditions.insert(pair<string, string>("guid", dbBuildRuleDependData.dependbuildruleid));
			DB::BuildRuleData *pBuildRuleDependData = dbBuildRuleDepend.query()->where(conditions)->first();
			if (pBuildRuleDependData)
			{
				sFileName = pBuildRuleDependData->targetfilename;
				sFilePath = pDBBuildRuleDeployData->deploypath;
				sFilePath += "depend/";
				sFilePath += pDBSourceCode->name;
				sFilePath += "/";
				sFilePath += pBuildRuleDependData->platform;
				sFilePath += "/";

				delete pBuildRuleDependData;
				delete pDBSourceCode;
				return true;
			}
			delete pDBSourceCode;
		}
		return false;
	}

	bool BuildRuleBuild::refresh_depend_file(string &sStorageId, string sFileAbsolutePath)
	{
		DB::Storage dbStorage;
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", sStorageId));
		DB::StorageData *pDBStorageData = dbStorage.query()->where(conditions)->first();
		if (pDBStorageData)
		{
			if (remove(sFileAbsolutePath.c_str()) != 0)
			{
				delete pDBStorageData;
				return false;
			}
			HttpClient hClient;
			if (!hClient.download_file(pDBStorageData->storagehostlist, sFileAbsolutePath))
			{
				delete pDBStorageData;
				return false;
			}
		}
		else
			return false;

		delete pDBStorageData;
		return true;
	}

	bool BuildRuleBuild::update_self(string &sWorkPath)
	{
		/*

		git_repository* rep = nullptr;

		git_remote* remote = nullptr;
		git_fetch_options fetch_opts = GIT_FETCH_OPTIONS_INIT;

		git_reference* origin_master = nullptr;
		git_reference* local_master = nullptr;
		const git_annotated_commit* their_head[10];
		git_commit* their_commit = nullptr;
		git_commit* our_commit = nullptr;
		git_merge_options merge_opt = GIT_MERGE_OPTIONS_INIT;
		git_checkout_options checkout_opt = GIT_CHECKOUT_OPTIONS_INIT;
		git_index* index = nullptr;
		git_index_conflict_iterator* conflict_iterator = nullptr;
		git_oid new_tree_id;
		git_tree* new_tree = nullptr;
		git_signature* me = nullptr;
		git_oid commit_id;

		int error = 0;

		// git open
		error = git_repository_open(&rep, pDBBuildRuleDeployData->deploypath.c_str());
		if (error < 0)
		{
			const git_error *e = giterr_last();
			std::cout << "Error: " << error << " / " << e->klass << " : " << e->message << std::endl;

			goto SHUTDOWN;
		}

		// get a remote
		error = git_remote_lookup(&remote, rep, "origin");

		// git fetch
		fetch_opts.callbacks.credentials = cred_acquire_cb;
		//    fetch_opts.prune = GIT_FETCH_PRUNE;    // --prune
		error = git_remote_fetch(remote, nullptr, &fetch_opts, nullptr);
		if (error < 0)
		{
			const git_error *e = giterr_last();
			std::cout << "Error: " << error << " / " << e->klass << " : " << e->message << std::endl;

			goto SHUTDOWN;
		}

		// merge
		error = git_branch_lookup(&origin_master, rep, "origin/master", GIT_BRANCH_REMOTE);
		error = git_branch_lookup(&local_master, rep, "master", GIT_BRANCH_LOCAL);

		error = git_repository_set_head(rep, git_reference_name(local_master));
		git_annotated_commit_from_ref((git_annotated_commit **)&their_head[0], rep, origin_master);

		error = git_merge(rep, their_head, 1, &merge_opt, &checkout_opt);
		if (error < 0)
		{
			const git_error *e = giterr_last();
			std::cout << "Error: " << error << " / " << e->klass << " : " << e->message << std::endl;

			goto SHUTDOWN;
		}

		// reslove conflicts
		git_repository_index(&index, rep);
		if (git_index_has_conflicts(index))
		{
			const git_index_entry* ancestor_out = nullptr;
			const git_index_entry* our_out = nullptr;
			const git_index_entry* their_out = nullptr;

			git_index_conflict_iterator_new(&conflict_iterator, index);

			while (git_index_conflict_next(&ancestor_out, &our_out, &their_out, conflict_iterator) != GIT_ITEROVER)
			{
				if (ancestor_out) std::cout << "ancestor: " << ancestor_out->path << std::endl;
				if (our_out) std::cout << "our: " << our_out->path << std::endl;
				if (their_out) std::cout << "their: " << their_out->path << std::endl;
			}

			// git checkout --theirs <file>
			git_checkout_options opt = GIT_CHECKOUT_OPTIONS_INIT;
			opt.checkout_strategy |= GIT_CHECKOUT_USE_THEIRS;
			git_checkout_index(rep, index, &opt);

			git_index_conflict_iterator_free(conflict_iterator);
		}

		git_commit_lookup(&their_commit, rep, git_reference_target(origin_master));
		git_commit_lookup(&our_commit, rep, git_reference_target(local_master));

		// add and commit
		error = git_index_update_all(index, nullptr, nullptr, nullptr);
		error = git_index_write(index);
		error = git_index_write_tree(&new_tree_id, index);
		error = git_tree_lookup(&new_tree, rep, &new_tree_id);

		git_signature_now(&me, "XiaochenFTX", "xiaochenftx@gmail.com");

		error = git_commit_create_v(&commit_id, rep, git_reference_name(local_master), me, me, "UTF-8", "pull commit", new_tree, 2, our_commit, their_commit);

		git_repository_state_cleanup(rep);

	SHUTDOWN:
		git_repository_free(rep);		*/

		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		// 清理因编译产生的影响文件
		ZeroMemory(&pi, sizeof(pi));
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		string sCmd = "git checkout .";
		if (!CreateProcessA(NULL, (char*)sCmd.c_str(), NULL, NULL, FALSE, 0, NULL, sWorkPath.c_str(), &si, &pi))
		{
			// 创建失败
			return false;
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		ZeroMemory(&pi, sizeof(pi));
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		sCmd = "git clean -xdf";
		if (!CreateProcessA(NULL, (char*)sCmd.c_str(), NULL, NULL, FALSE, 0, NULL, sWorkPath.c_str(), &si, &pi))
		{
			// 创建失败
			return false;
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		// 获取新的文件
		ZeroMemory(&pi, sizeof(pi));
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		sCmd = "git pull";
		if (!CreateProcessA(NULL, (char*)sCmd.c_str(), NULL, NULL, FALSE, 0, NULL, sWorkPath.c_str(), &si, &pi))
		{
			// 创建失败
			return false;
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return true;
	}

	bool BuildRuleBuild::analysis_logs(DB::BuildRuleData *pDBBuildRuleData, DB::BuildRule_DeployData *pDBBuildRuleDeployData, string &sWorkPath)
	{
		DB::Resource_SourceCode dbSourceCode;
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", pDBBuildRuleData->sourcecodeid));
		DB::Resource_SourceCodeData *pDBSourceCodeData = dbSourceCode.query()->where(conditions)->first();
		if (!pDBSourceCodeData)
			return false;

		DB::BuildResultData dbBuildResultData;
		dbBuildResultData.guid = getGUID();
		dbBuildResultData.buildruleid = pDBBuildRuleData->guid;
		dbBuildResultData.version = pDBSourceCodeData->currentversion + 1;
		delete pDBSourceCodeData;

		// 检查编译是否成功，标志为目标文件是否生成
		if (is_build_successed(sWorkPath, pDBBuildRuleData))
		{
			// 编译成功
			dbBuildResultData.status = 0;
			dbBuildResultData.log = "";
			string sTargetFilePath = sWorkPath + "\\" + pDBBuildRuleData->targetfilepath + "\\" + pDBBuildRuleData->targetfilename;
			if (upload_file(dbBuildResultData.storageid, pDBBuildRuleData->targetfilename,sTargetFilePath))
			{
				dbBuildResultData.status = 0;
			}
			else
			{
				dbBuildResultData.storageid = "";
				dbBuildResultData.status = 1;
			}
		}
		else
		{
			// 编译失败
			// 读取日志文件
			string sLogContent = "";
			ifstream ifs;
			ifs.open(sWorkPath + "\\" + pDBBuildRuleData->logfilepath + pDBBuildRuleData->logfilename);
			if (ifs.is_open())
			{
				std::stringstream buffer;
				buffer << ifs.rdbuf();
				sLogContent = buffer.str();
				g2u(sLogContent.c_str(), sLogContent.length(), m_szBuf, Buffer_Size);
				sLogContent = m_szBuf;
				ifs.close();
			}
			dbBuildResultData.log = sLogContent;
			dbBuildResultData.storageid = "";
			dbBuildResultData.status = 1;
		}

		DB::BuildResult dbBuildResult;
		if (!dbBuildResult.create(dbBuildResultData)->exec())
			return false;
		return true;
	}

	bool BuildRuleBuild::is_build_successed(string &sWorkPath, DB::BuildRuleData *pDBBuildRuleData)
	{
		string sTargetFilePath = sWorkPath + "\\" + pDBBuildRuleData->targetfilepath + "\\" + pDBBuildRuleData->targetfilename;
		ifstream ifs;
		ifs.open(sTargetFilePath);
		if (ifs.is_open())
		{
			ifs.close();
			return true;
		}
		return false;
	}

	bool BuildRuleBuild::upload_file(string &sStorageId, string sFileName, string sFileAbsolutePath)
	{
		// 获取文件信息
		FILE *fp = fopen(sFileAbsolutePath.c_str(), "rb");
		if (fp)
		{
			fseek(fp, 0, SEEK_END);
			long lFileSize = ftell(fp);

			DB::Resource_Host dbHost;
			vector<DB::Resource_HostData> *pVecDBHostData = dbHost.query()->where("`type`=0x00000001")->all();
			string sPartition = "";
			string sHostId = "";
			string sHostAddress = "";
			int nPort = 0;
			if (pVecDBHostData)
			{
				for (int nIndex = 0; nIndex < pVecDBHostData->size(); nIndex++)
				{
					DB::Resource_HostData &hostData = (*pVecDBHostData)[nIndex];
					Json::Reader jsonReader;
					Json::Value jsonStorage;
					if (!jsonReader.parse(hostData.storage, jsonStorage))
					{
						fclose(fp);
						return false;
					}
					Json::Value jsonAvaSpace = jsonStorage["availableSpace"];
					for (int n = 0; n < jsonAvaSpace.size(); n++)
					{
						string sSpace = jsonAvaSpace[n].asString();
						long lSpace = atol(sSpace.c_str());
						if (lSpace > lFileSize)
						{
							Json::Value jsonPartition = jsonStorage["partitionName"];
							sPartition = jsonPartition[n].asString();
							sHostId = hostData.guid;
							sHostAddress = hostData.address;
							nPort = hostData.port;
							break;
						}
					}
				}
			}
			if (sPartition.compare("") == 0)
			{
				fclose(fp);
				return false;
			}

			// 准备上传文件
			DB::StorageData dbStorageData;
			HttpClient httpClient;
			if (httpClient.upload_file(sHostAddress, nPort, "", sFileName, sFileAbsolutePath))
			{
				Json::Value jsonPathList;
				Json::Value  jsonHostPath;
				jsonHostPath["hostid"] = sHostId;
				char szBuf[255];
				sprintf(szBuf, "0-%ld", lFileSize);
				jsonHostPath["range"] = szBuf;
				jsonHostPath["name"] = "";
				sprintf(szBuf, ":\\VersionBuild\\storage\\%s", sPartition.c_str(), dbStorageData.guid);
				jsonHostPath["path"] = szBuf;
				jsonPathList.append(jsonHostPath);

				dbStorageData.guid = httpClient.repsonse_data()["data"].asString();
				dbStorageData.storagehostlist = Json::FastWriter().write(jsonPathList);;
				dbStorageData.name = "";
				dbStorageData.size = lFileSize;
				dbStorageData.md5 = file_md5(sFileAbsolutePath);
				DB::Storage dbStorage;
				if (!dbStorage.create(dbStorageData)->exec())
				{
					fclose(fp);
					return false;
				}
				sStorageId = dbStorageData.guid;
			}
			fclose(fp);
		}
		else
			return false;

		return true;
	}

	bool BuildRuleBuild::end_task(DB::BuildRuleData *pDBBuildRuleData)
	{
		bool bOut = false;
		while (!bOut)
		{
			DB::Resource_SourceCode dbSourceCode;
			DB::Conditions conditions;
			conditions.insert(pair<string, string>("guid", pDBBuildRuleData->sourcecodeid));
			DB::Resource_SourceCodeData *pSourceCodeData = dbSourceCode.query()->where(conditions)->first();
			if (pSourceCodeData)
			{
				mysqlpp::sql_int sqlnNewBuildState = pSourceCodeData->buildstate | pDBBuildRuleData->innerid;
				if (sqlnNewBuildState == pSourceCodeData->buildstatemask)
				{
					set<string> setFilter;
					setFilter.insert("currentversion");
					setFilter.insert("status");
					setFilter.insert("buildstate");
					DB::Resource_SourceCodeData dbSourceCodeData;
					dbSourceCodeData.status = 2;
					dbSourceCodeData.buildstate = sqlnNewBuildState;
					dbSourceCodeData.currentversion = pSourceCodeData->currentversion + 1;
					char szBuf[255] = { 0 };
					sprintf(szBuf, "`guid`='%s' and `buildstate`=%d", pDBBuildRuleData->sourcecodeid.c_str(), pSourceCodeData->buildstate);
					bOut = dbSourceCode.update(setFilter, dbSourceCodeData)->where(szBuf)->exec();
				}
				delete pSourceCodeData;
			}
			else
				return false;
		}
		return true;
	}
}