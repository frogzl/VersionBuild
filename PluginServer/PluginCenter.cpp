#include "PluginCenter.h"
#include <io.h>
#include "Common.h"
#include <Windows.h>
#include <assert.h>
map<string, PluginService*> PluginCenter::mPluginService;
HANDLE PluginCenter::hPluginServiceMutex = NULL;

void PluginCenter::load_service_plugins()
{
	if (!hPluginServiceMutex)
		hPluginServiceMutex = CreateMutex(NULL, FALSE, NULL);

	char szPath[255];
	map<string, string> mDll;
	enum_dll_path(0, app_root_path() + "MicroServicePlugins", 2, mDll);
	map<string, string>::iterator it = mDll.begin();
	while (it != mDll.end())
	{
		GetCurrentDirectoryA(255, szPath);
		SetCurrentDirectoryA(it->first.c_str());
		PluginService *pPlugin = new PluginService(it->second);
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
		it++;
	}
}

void PluginCenter::install_service_plugin(const char *szPluginID, const char *szPluginVersion)
{
	assert(false);
}

void PluginCenter::uninstall_service_plugin(const char *szPluginID, const char *szPluginVersion)
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

void PluginCenter::free_service(Service *&pService)
{
	delete pService;
	pService = NULL;
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
	PluginService *pPlugin= NULL;
	WaitForSingleObject(hPluginServiceMutex, INFINITE);
	map<string, PluginService*>::iterator itFind = mPluginService.find(generate_plugin_key(szPluginID, szPluginVersion));
	if (itFind != mPluginService.end())
		pPlugin = itFind->second;
	ReleaseMutex(hPluginServiceMutex);
	return pPlugin;
}

void PluginCenter::enum_dll_path(int nLayer, string sPath, int nDepth, map<string, string> &mDll)
{
	if (nLayer > nDepth)
		return;

	_finddata_t fd;
	string sTmp = "";
	if (nLayer == nDepth)
	{
		sTmp = sPath + "\\plugin_*.dll";
		intptr_t pf = _findfirst(sTmp.c_str(), &fd);
		if (pf != -1)
		{
			do {
				printf("%s\n", fd.name);
				mDll.insert(pair<string, string>(sPath, fd.name));
			} while (!_findnext(pf, &fd));
			_findclose(pf);
		}
	}
	else
	{
		sTmp = sPath + "\\*";
		intptr_t pf = _findfirst(sTmp.c_str(), &fd);
		if (pf != -1)
		{
			do
			{
				if (((int)fd.attrib & _A_SUBDIR) == _A_SUBDIR)
				{
					if (strcmp(".", fd.name) != 0 && strcmp("..", fd.name) != 0)
					{
						printf("%s ", fd.name);
						enum_dll_path(nLayer + 1, sPath + "\\" + fd.name, nDepth, mDll);
					}
				}
			} while (!_findnext(pf, &fd));

			_findclose(pf);
		}
	}
}