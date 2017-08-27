#include "Deploy.h"
#include "../SystemConfig.h"
#include "../Common.h"
#include "Helper.h"
using namespace Helper;
Deploy::Deploy(TaskData *pTD) :m_pTD(pTD)
{
}

Deploy::~Deploy()
{
}
/*
{
"unique_id":"7d11f0f8-ab96-4532-b5a7-4b8d9191e436",
"version":"1",
"task_path":"/7d11f0f8-ab96-4532-b5a7-4b8d9191e436/1/sourcecode/build",
"plugin_deploy_id":"",
"source_code_id":"",
"source_code_folder":"",
"build_rule_id":"",
"deploy_commands":"",
"depends":[
{"build_result_id":"","storage_id":"","alias":""},
{"build_result_id":"","storage_id":"","alias":""},
{"build_result_id":"","storage_id":"","alias":""},
{"build_result_id":"","storage_id":"","alias":""}
],
"finish_url":"/source-code/{id}/build-rule/{id}/deploy-result"
}
*/

void Deploy::process_task()
{
	char szBuf[255];
	// 寻找可用的存储位置
	string sDeployDir = "";
	ULONGLONG llMax = 0;
	for (int nIndex = 0; nIndex < SystemConfig::instance()->vecPartition.size(); nIndex++)
	{
		ULONGLONG llTmp = get_dir_free_size(SystemConfig::instance()->vecPartition[nIndex]);
		if (llTmp > llMax)
		{
			sDeployDir = SystemConfig::instance()->vecPartition[nIndex];
			break;
		}
	}
	if (sDeployDir.compare("") == 0)
	{
		send_back_result("1", "no space for file.");
		return;
	}

	// 可用部署位置
	sDeployDir += "\\deploy";
	if (_access(sDeployDir.c_str(), 0) != 0) _mkdir(sDeployDir.c_str());
	sDeployDir += ("\\" + m_pTD->data()["source_code_id"].asString());
	if (_access(sDeployDir.c_str(), 0) != 0) _mkdir(sDeployDir.c_str());
	sDeployDir += ("\\" + m_pTD->data()["build_rule_id"].asString());
	if (_access(sDeployDir.c_str(), 0) != 0) _mkdir(sDeployDir.c_str());
	string sTmpDir = sDeployDir + "\\tmp";
	if (_access(sTmpDir.c_str(), 0) != 0) _mkdir(sTmpDir.c_str());

	// 获取部署命令
	string sCmds = m_pTD->data()["deploy_commands"].asString();
	vector<string> vecCmds;
	split(sCmds, ";", &vecCmds);
	ULONGLONG llDeployBeforeSize = get_dir_free_size(sDeployDir);
	for (int nIndexCmd = 0; nIndexCmd < vecCmds.size(); nIndexCmd++)
		run_command(vecCmds[nIndexCmd], sDeployDir);
	ULONGLONG llDeployAfterSize = get_dir_free_size(sDeployDir);
	if (llDeployAfterSize == llDeployBeforeSize)
	{
		send_back_result("1", "failed to deploy.");
		return;
	}

	// 下载依赖
	Json::Value jDepends = m_pTD->data()["deploy_commands"];
	for (int nIndexDepend = 0; nIndexDepend < jDepends.size(); nIndexDepend++)
	{
		Json::Value jDepend = jDepends[nIndexDepend];
		sprintf(szBuf, "/file/{%s}", jDepend["storage_id"].asString().c_str());
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
	string sRecordFile = sDeployDir + "/record";
	FILE  *fp = fopen(sRecordFile.c_str(), "wb");
	if (fp)
	{
		string sData = Json::FastWriter().write(jDepends);
		fwrite(sData.c_str(), 1, sData.length(), fp);
		fclose(fp);
	}

	Json::Value jValue;
	jValue["deploy_path"] = sDeployDir;
	send_back_result("0", "success.", jValue);
}

ULONGLONG  Deploy::get_dir_free_size(string sDirName)
{
	ULARGE_INTEGER nFreeBytesAvailable;
	ULARGE_INTEGER nTotalNumberOfBytes;
	ULARGE_INTEGER nTotalNumberOfFreeBytes;
	if (GetDiskFreeSpaceExA(sDirName.c_str(), &nFreeBytesAvailable, &nTotalNumberOfBytes, &nTotalNumberOfFreeBytes))
		return nFreeBytesAvailable.QuadPart;
	else
		return 0;
}

void Deploy::run_command(string sCmd, string sWorkPath)
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

void Deploy::send_back_result(string sCode, string sMsg)
{
	Network::Request_Data rd;
	Json::Value jRequest;
	jRequest["code"] = sCode;
	jRequest["message"] = sMsg;
	rd.sData = Json::FastWriter().write(jRequest);
	Network::post(Network::enReverseProxy, "e2cb8547-7aa0-4fe0-bad0-0f974d9270c6", "1", m_pTD->data()["finish_url"].asString(), rd, NULL, NULL);
}

void Deploy::send_back_result(string sCode, string sMsg, Json::Value jValue)
{
	Network::Request_Data rd;
	Json::Value jRequest;
	jRequest["code"] = sCode;
	jRequest["message"] = sMsg;
	jRequest["data"] = jValue;
	rd.sData = Json::FastWriter().write(jRequest);
	Network::post(Network::enReverseProxy, "e2cb8547-7aa0-4fe0-bad0-0f974d9270c6", "1", m_pTD->data()["finish_url"].asString(), rd, NULL, NULL);
}