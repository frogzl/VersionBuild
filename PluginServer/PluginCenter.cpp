#include "PluginCenter.h"
#include <io.h>
#include "Common.h"
#include <Windows.h>
#include <assert.h>
map<string, PluginService*> PluginCenter::mPluginService;
map<string, PluginTask*> PluginCenter::mPluginTask;

void PluginCenter::load_service_plugins()
{
	char szPath[255];
	GetModuleFileNameA(NULL, szPath, 255);
	std::string sPath(szPath);
	int nPos = (int)sPath.find("PluginServer.exe", 0);
	int nNameSize = sizeof("PluginServer.exe");
	sPath.erase(nPos, nNameSize - 1);
	string sPluginServicePath = sPath + "MicroServicePlugins";
	string sTmp = sPluginServicePath + "\\*.dll";
	_finddata_t fd;
	intptr_t pf = _findfirst(sTmp.c_str(), &fd);
	while (!_findnext(pf, &fd))
	{
		if (strcmp("MicroServicePlugin.dll", fd.name) == 0)
			continue;

		std::string sDll = sPluginServicePath + "\\" + fd.name;
		GetCurrentDirectoryA(255, szPath);
		SetCurrentDirectoryA(sPluginServicePath.c_str());
		PluginService *pPlugin = new PluginService(fd.name);
		SetCurrentDirectoryA(szPath);
		if (pPlugin->enable())
		{
			string sKey = generate_plugin_key(pPlugin->unique_id(), pPlugin->version());
			map<string, PluginService*>::iterator itFind = mPluginService.find(sKey);
			if (itFind == mPluginService.end())
				mPluginService.insert(pair<string, PluginService*>(sKey, pPlugin));
			else
				delete pPlugin;
		}
		else
			delete pPlugin;
	}
	_findclose(pf);
}

void PluginCenter::load_task_plugins()
{
	char szPath[255];
	GetModuleFileNameA(NULL, szPath, 255);
	std::string sPath(szPath);
	int nPos = (int)sPath.find("PluginServer.exe", 0);
	int nCount = sizeof("PluginServer.exe");
	sPath.erase(nPos, nCount - 1);
	std::string sPluginTaskPath = sPath + "MicroTaskPlugins";

}

void PluginCenter::install_service_plugin(const char *szPluginID, const char *szPluginVersion)
{
	assert(false);
}

void PluginCenter::install_task_plugin(const char *szPluginID, const char *szPluginVersion)
{
	assert(false);
}

void PluginCenter::uninstall_service_plugin(const char *szPluginID, const char *szPluginVersion)
{
	assert(false);
}

void PluginCenter::uninstall_task_plugin(const char *szPluginID, const char *szPluginVersion)
{
	assert(false);
}

Service* PluginCenter::parse_service_path(const char *szOperator, const char *szPath)
{
	Service *pService = new Service();
	if (analysis_service_path(szOperator, szPath, pService))
		return pService;
	delete pService;
	return 0;
}

Task* PluginCenter::parse_task_path()
{
	return 0;
}

void PluginCenter::free_service(Service *&pService)
{
	delete pService;
	pService = NULL;
}

void PluginCenter::free_task(Task *&pTask)
{
	assert(false);
}

void PluginCenter::destory()
{
	map<string, PluginService*>::iterator it = mPluginService.begin();
	while (it != mPluginService.end())
		delete it->second;
}

string PluginCenter::generate_plugin_key(const char *szPluginID, const char *szPluginVersion)
{
	string sSplit = "_";
	return szPluginID + sSplit + szPluginVersion;
}

bool PluginCenter::analysis_service_path(const char *szOperator, const char *szPath, Service *pService)
{
	std::vector<std::string> vecItem;
	split(szPath, "/", vecItem);
	if (vecItem.size() < 3)
		return false;

	PluginService *pPlugin = enum_service_plugin(vecItem[1].c_str(), vecItem[2].c_str());
	if (!pPlugin)
		return false;
	pService->setData(pPlugin->create_data());
	int nCreateIndex = pPlugin->parse_path(szOperator, szPath, pService->data()->request_data().vecParameters);
	if (nCreateIndex != -1)
	{

		pService->setCreateIndex(nCreateIndex);
		pService->setPlugin(pPlugin);
		return true;
	}
	else
		return false;
}

PluginService* PluginCenter::enum_service_plugin(const char *szPluginID, const char *szPluginVersion)
{
	map<string, PluginService*>::iterator itFind = mPluginService.find(generate_plugin_key(szPluginID, szPluginVersion));
	if (itFind != mPluginService.end())
		return itFind->second;
	else
		return NULL;
}