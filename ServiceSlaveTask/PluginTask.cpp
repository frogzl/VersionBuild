#include "PluginTask.h"
PluginTask::PluginTask(std::string sPath)
{
	pTaskIf = NULL;
	func_produce_one = NULL;
	bEnable = false;
	hDll = NULL;
	hRouteMutex = NULL;

	if (init_functions(sPath))
	{
		pTaskIf = func_produce_one();
		if (!pTaskIf)
		{
			FreeLibrary(hDll);
			hDll = NULL;
			bEnable = false;
			return;
		}
		else
		{
			Task_Route_Info *tri = NULL;
			int nRouteCount = pTaskIf->route_infos(tri);
			for (int nIndexRoute = 0; nIndexRoute < nRouteCount; nIndexRoute++)
			{
				map<string, int>::iterator itFind = mRoutes.find(tri[nIndexRoute].szPath);
				if (itFind != mRoutes.end())
					mRoutes[tri[nIndexRoute].szPath] = tri[nIndexRoute].nIndex;
				else
					mRoutes.insert(pair<string, int>(tri[nIndexRoute].szPath, tri[nIndexRoute].nIndex));
			}
			hRouteMutex = CreateMutex(nullptr, FALSE, nullptr);
			if (hRouteMutex)
				bEnable = true;
			else
				bEnable = false;
		}
	}
	else
		bEnable = false;
}

PluginTask::~PluginTask()
{
	if (hRouteMutex) CloseHandle(hRouteMutex);
}

bool PluginTask::dispatch(int nIndex, TaskData *pD)
{
	return pTaskIf->dispatch_by_route_path(nIndex, pD);
}

int PluginTask::parse_path(const char *szPath)
{
	WaitForSingleObject(hRouteMutex, INFINITE);
	map<string, int>::iterator itFind = mRoutes.find(szPath);
	if (itFind != mRoutes.end())
	{
		int nIndex = itFind->second;
		ReleaseMutex(hRouteMutex);
		return nIndex;
	}
	ReleaseMutex(hRouteMutex);
	return -1;
}

bool PluginTask::init_functions(string &sPath)
{
	hDll = LoadLibraryA(sPath.c_str());
	if (hDll)
	{
		func_produce_one = (FUNCProduceOne)GetProcAddress(hDll, "produce_one");
		if (!func_produce_one)
		{
			FreeLibrary(hDll); hDll = NULL;
			return false;
		}
		return true;
	}
	else
		return false;
}
