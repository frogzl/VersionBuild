#include "Build.h"
#include "../SystemConfig.h"
#include "../Common.h"
#include "Helper.h"
using namespace Helper;
Build::Build(TaskData *pTD) :m_pTD(pTD)
{
}

Build::~Build()
{
}

/*
{
"unique_id":"7d11f0f8-ab96-4532-b5a7-4b8d9191e436",
"version":"1",
"task_path":"/7d11f0f8-ab96-4532-b5a7-4b8d9191e436/1/sourcecode/build",
"plugin_deploy_id":"",
"source_code_id":"",
"build_rule_id":"",
"update_commands":"",
"compile_cmd":"",
"source_code_folder":"",
"deploy_path":"",
"target":{
"file_name":"",
"file_path":"",
"output_directory_template":""
},
"depends":[
{"build_result_id":"","storage_id":"","alias":""},
{"build_result_id":"","storage_id":"","alias":""},
{"build_result_id":"","storage_id":"","alias":""},
{"build_result_id":"","storage_id":"","alias":""}
],
"finish_url":"/source-code/{id}/build-rule/{id}/build-result"
}
*/
void Build::process_task()
{
	char szBuf[255];
	// 可用部署位置
	string sDeployDir = m_pTD->data()["deploy_path"].asString();
	if (_access(sDeployDir.c_str(), 0) != 0)
	{
		send_back_result("1", "failed find deploy position.");
		return;
	}
	string sTmpDir = sDeployDir + "\\tmp";
	if (_access(sTmpDir.c_str(), 0) != 0) _mkdir(sTmpDir.c_str());

	// 获取更新命令
	string sCmds = m_pTD->data()["update_commands"].asString();
	vector<string> vecCmds;
	split(sCmds, ";", &vecCmds);
	ULONGLONG llDeployBeforeSize = get_dir_free_size(sDeployDir);
	string sGit = sDeployDir + "/" + m_pTD->data()["source_code_folder"].asString();
	for (int nIndexCmd = 0; nIndexCmd < vecCmds.size(); nIndexCmd++)
		run_command(vecCmds[nIndexCmd], sGit);
	ULONGLONG llDeployAfterSize = get_dir_free_size(sDeployDir);
	if (llDeployAfterSize == llDeployBeforeSize)
	{
		send_back_result("1", "failed to deploy.");
		return;
	}

	// 更新依赖
	map<string, string> mResultIDAndStorageID;
	string sRecordFile = sDeployDir + "/record";
	FILE  *fp = fopen(sRecordFile.c_str(), "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		long lFileSize = ftell(fp);
		char *szData = new char[lFileSize + 1];
		memset(szData, 0, lFileSize + 1);
		fseek(fp, 0, SEEK_SET);
		fread(szData, lFileSize, 1, fp);
		Json::Value jRecord;
		Json::Reader reader;
		if (reader.parse(szData, jRecord))
		{
			for (int nIndex = 0; nIndex < jRecord.size(); nIndex++)
			{
				Json::Value jValue = jRecord[nIndex];
				mResultIDAndStorageID.insert(pair<string, string>(jValue["build_result_id"].asString(), jValue["storage_id"].asString()));
			}
		}
		fclose(fp);
	}

	Json::Value jNewDepends = m_pTD->data()["depends"];
	for (int nIndexDepend = 0; nIndexDepend < jNewDepends.size(); nIndexDepend++)
	{
		Json::Value jValue = jNewDepends[nIndexDepend];
		map<string, string>::iterator itFind = mResultIDAndStorageID.find(jValue["build_result_id"].asString());
		if (itFind == mResultIDAndStorageID.end() || jValue["storage_id"].asString().compare(itFind->second) != 0)
		{
			sprintf(szBuf, "/file/{%s}", jValue["storage_id"].asString().c_str());
			string sInOut = sTmpDir;
			if (Network::download("f1f1420f-f69d-44cc-a454-313d05f81959", "1", szBuf, sInOut))
			{
				sprintf(szBuf, "WinRAR.exe e - y %s/%s %s", sTmpDir.c_str(), sInOut.c_str(), sDeployDir.c_str());
				run_command(szBuf, sDeployDir);
				string sTmpFile = sTmpDir + "/" + sInOut;
				remove(sTmpFile.c_str());
			}
			else
			{
				send_back_result("1", "depend download failed.");
				return;
			}

		}
	}

	string sRecordFile = sDeployDir + "/record";
	FILE  *fp = fopen(sRecordFile.c_str(), "wb");
	if (fp)
	{
		string sData = Json::FastWriter().write(jNewDepends);
		fwrite(sData.c_str(), 1, sData.length(), fp);
		fclose(fp);
	}


	// 编译源码
	string sCmds = m_pTD->data()["compile_cmd"].asString();
	vector<string> vecCmds;
	split(sCmds, ";", &vecCmds);
	for (int nIndexCmd = 0; nIndexCmd < vecCmds.size(); nIndexCmd++)
		run_command(vecCmds[nIndexCmd], sGit);
	if (llDeployAfterSize == llDeployBeforeSize)
	{
		send_back_result("1", "failed to compile.");
		return;
	}

	// 判断是否编译成功
	string sTarget = sGit + "/" + m_pTD->data()["file_path"].asString() +"/" + m_pTD->data()["file_name"].asString();
	if (_access(sTarget.c_str(), 0) != 0)
		send_back_result("1", "compile failed.");

	// 制作文件包
	Json::Value jOutputDirTemp = m_pTD->data()["output_directory_template"];
	string sInstallPackage = sTmpDir + "/" + m_pTD->data()["source_code_folder"].asString();
	if (_access(sInstallPackage.c_str(), 0) != 0)
		_mkdir(sInstallPackage.c_str());
	for (int nIndex = 0; nIndex < jOutputDirTemp.size(); nIndex++)
	{
		Json::Value jDir = jOutputDirTemp[nIndex];
		string sDir = sInstallPackage + "/" + jDir["node_name"].asString();
		if (_access(sDir.c_str(), 0) != 0) 
			_mkdir(sDir.c_str());
		Json::Value jValues = jDir["value"];
		for (int nIndexValue = 0; nIndexValue < jValues.size(); nIndexValue++)
		{
			string sValue = jValues[nIndexValue].asString();
			string sFrom = sGit + "/" + sValue;
			int nPos = sValue.rfind('/');
			string sTo = sDir + "/" + sValue.substr(sValue.length() - nPos);

			FILE *fpFrom = fopen(sFrom.c_str(), "rb");
			FILE *fpTo = fopen(sTo.c_str(), "wb");
			if (!fpFrom) continue;
			if (!fpTo) { fclose(fpFrom); continue; }
			while (!feof(fpFrom))
			{
				size_t stRead = fread(szBuf, 1, 255, fpFrom);
				fwrite(szBuf, 1, stRead, fpTo);
			}
			fclose(fpFrom);
			fclose(fpTo);
		}
	}
	sprintf(szBuf, "winrar.exe a -ag -k -r -s -ibck %s.rar %s/",sInstallPackage.c_str(), sInstallPackage.c_str());
	run_command(szBuf, sTmpDir);

	string sStorageID = "";
	sprintf(szBuf, "%s.rar", sInstallPackage.c_str());
	if (!Network::upload("f1f1420f-f69d-44cc-a454-313d05f81959", "1", "/file",szBuf, sStorageID))
		send_back_result("1", "failed to upload result.");
	Json::Value jRespond;
	jRespond["storage_id"] = sStorageID;
	send_back_result("0", "successed", jRespond);
}

void Build::run_command(string sCmd, string sWorkPath)
{
	// 执行部署命令
	SHELLEXECUTEINFOA si;
	ZeroMemory(&si, sizeof(si));
	si.cbSize = sizeof(si);
	si.fMask = SEE_MASK_NOCLOSEPROCESS;
	si.lpVerb = "open";
	si.lpFile = sCmd.c_str();
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
}

void Build::send_back_result(string sCode, string sMsg)
{
	Network::Request_Data rd;
	Json::Value jRequest;
	jRequest["code"] = sCode;
	jRequest["message"] = sMsg;
	rd.sData = Json::FastWriter().write(jRequest);
	Network::post(Network::enReverseProxy, "e2cb8547-7aa0-4fe0-bad0-0f974d9270c6", "1", m_pTD->data()["finish_url"].asString(), rd, NULL, NULL);
}

void Build::send_back_result(string sCode, string sMsg, Json::Value jValue)
{
	Network::Request_Data rd;
	Json::Value jRequest;
	jRequest["code"] = sCode;
	jRequest["message"] = sMsg;
	jRequest["data"] = jValue;
	rd.sData = Json::FastWriter().write(jRequest);
	Network::post(Network::enReverseProxy, "e2cb8547-7aa0-4fe0-bad0-0f974d9270c6", "1", m_pTD->data()["finish_url"].asString(), rd, NULL, NULL);
}

ULONGLONG  Build::get_dir_free_size(string sDirName)
{
	ULARGE_INTEGER nFreeBytesAvailable;
	ULARGE_INTEGER nTotalNumberOfBytes;
	ULARGE_INTEGER nTotalNumberOfFreeBytes;
	if (GetDiskFreeSpaceExA(sDirName.c_str(), &nFreeBytesAvailable, &nTotalNumberOfBytes, &nTotalNumberOfFreeBytes))
		return nFreeBytesAvailable.QuadPart;
	else
		return 0;
}