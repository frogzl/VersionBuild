#include "PluginCenter.h"
#include <io.h>
#include "Common.h"
#include <Windows.h>
#include <assert.h>
map<string, PluginTask*> PluginCenter::mPluginTask;
HANDLE PluginCenter::hPluginTaskMutex = NULL;

void PluginCenter::load_task_plugins()
{
	if (!hPluginTaskMutex)
		hPluginTaskMutex = CreateMutex(NULL, FALSE, NULL);

	char szPath[255];
	map<string, string> mDll;
	enum_dll_path(0, app_root_path() + "MicroTaskPlugins", 2, mDll);
	map<string, string>::iterator it = mDll.begin();
	while (it != mDll.end())
	{
		GetCurrentDirectoryA(255, szPath);
		SetCurrentDirectoryA(it->first.c_str());
		PluginTask *pPlugin = new PluginTask(it->second);
		SetCurrentDirectoryA(szPath);
		if (pPlugin->enable())
		{
			string sKey = generate_plugin_key(pPlugin->unique_id(), pPlugin->version());
			map<string, PluginTask*>::iterator itFind = mPluginTask.find(sKey);
			if (itFind == mPluginTask.end())
				mPluginTask.insert(pair<string, PluginTask*>(sKey, pPlugin));
			else
				delete pPlugin;
		}
		else
			delete pPlugin;
		it++;
	}
}

void PluginCenter::install_task_plugin(const char *szPluginID, const char *szPluginVersion)
{
	assert(false);
}

void PluginCenter::uninstall_task_plugin(const char *szPluginID, const char *szPluginVersion)
{
	assert(false);
}

Task* PluginCenter::parse_task_path(const char *szPath)
{
	Task *pTask = new Task();
	if (analysis_task_path(szPath, pTask))
		return pTask;
	delete pTask;
}

void PluginCenter::free_task(Task *&pTask)
{
	delete pTask;
	pTask = NULL;
}

void PluginCenter::destory()
{
	map<string, PluginTask*>::iterator it = mPluginTask.begin();
	while (it != mPluginTask.end())
		delete it->second;
}

string PluginCenter::generate_plugin_key(const char *szPluginID, const char *szPluginVersion)
{
	string sSplit = "_";
	return szPluginID + sSplit + szPluginVersion;
}

bool PluginCenter::analysis_task_path(const char *szPath, Task *pTask)
{
	std::vector<std::string> vecItem;
	split(szPath, "/", vecItem);
	if (vecItem.size() < 3)
		return false;

	PluginTask *pPlugin = enum_task_plugin(vecItem[1].c_str(), vecItem[2].c_str());
	if (!pPlugin)
		return false;

	pTask->setData(pPlugin->create_data());
	int nCreateIndex = pPlugin->parse_path(szPath);
	if (nCreateIndex != -1)
	{

		pTask->setCreateIndex(nCreateIndex);
		pTask->setPlugin(pPlugin);
		return true;
	}
	else
		return false;
}

PluginTask* PluginCenter::enum_task_plugin(const char *szPluginID, const char *szPluginVersion)
{
	PluginTask *pPlugin= NULL;
	WaitForSingleObject(hPluginTaskMutex, INFINITE);
	map<string, PluginTask*>::iterator itFind = mPluginTask.find(generate_plugin_key(szPluginID, szPluginVersion));
	if (itFind != mPluginTask.end())
		pPlugin = itFind->second;
	ReleaseMutex(hPluginTaskMutex);
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