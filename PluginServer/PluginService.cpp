#include "PluginService.h"
PluginService::PluginService(std::string sPath)
{
	pServiceIf = NULL;
	func_produce_one = NULL;
	bEnable = false;
	hDll = NULL;
	hRouteMutex = NULL;

	if (init_functions(sPath))
	{
		pServiceIf = func_produce_one();
		if (!pServiceIf)
		{
			FreeLibrary(hDll);
			hDll = NULL;
			bEnable = false;
			return;
		}
		else
		{
			Route_Info *ri = NULL;
			int nRouteCount = pServiceIf->route_infos(ri);
			for (int nIndexRoute = 0; nIndexRoute < nRouteCount; nIndexRoute++)
			{
				map<string, RoutePart>::iterator itFind = mRoutes.find(ri[nIndexRoute].szOperation);
				if (itFind != mRoutes.end())
					itFind->second.insert(ri[nIndexRoute].szPath, ri[nIndexRoute].nIndex);
				else
				{
					mRoutes.insert(pair<string, RoutePart>(ri[nIndexRoute].szOperation, RoutePart()));
					mRoutes[ri[nIndexRoute].szOperation].insert(ri[nIndexRoute].szPath, ri[nIndexRoute].nIndex);
				}
			}
			hRouteMutex= CreateMutex(nullptr, FALSE, nullptr);
			if (hRouteMutex)
				bEnable = true;
			else
				bEnable = false;
		}
	}
	else
		bEnable = false;
}

PluginService::~PluginService()
{
	if (hRouteMutex) CloseHandle(hRouteMutex);
}

bool PluginService::init_functions(string &sPath)
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

bool PluginService::dispatch(int nIndex, ServiceData *pD)
{
	return pServiceIf->dispatch_by_route_path(nIndex, pD);
}

int PluginService::parse_path(const char *szOperation, const char *szPath, vector<string> &vecParameters)
{
	WaitForSingleObject(hRouteMutex, INFINITE);
	map<string, RoutePart>::iterator itFind = mRoutes.find(szOperation);
	if (itFind != mRoutes.end())
	{
		RoutePart &rp = itFind->second;
		ReleaseMutex(hRouteMutex);
		return rp.parse_path(szPath, vecParameters);
	}
	ReleaseMutex(hRouteMutex);
	return -1;
}