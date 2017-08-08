#include "PluginService.h"
PluginService::PluginService(std::string sPath)
{
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
				bEnable = true;
			}
	}
	else
		bEnable = false;
}

PluginService::~PluginService()
{
}

bool PluginService::init_functions(string &sPath)
{
	hDll = LoadLibraryA(sPath.c_str());
	if (hDll)
	{
		func_produce_one = (FUNCProduceOne)GetProcAddress(hDll, "produce_one");
		if (!func_produce_one)
		{
			int n = GetLastError();
			FreeLibrary(hDll); hDll = NULL;
			return false;
		}
		return true;
	}
	else
	{
		int nR = GetLastError();
		return false;
	}

}

bool PluginService::dispatch(int nIndex, ServiceData *pD)
{
	return pServiceIf->dispatch_by_route_path(nIndex, pD);
}

int PluginService::parse_path(const char *szOperator, const char *szPath, vector<string> &vecParameters)
{
	return -1;
}