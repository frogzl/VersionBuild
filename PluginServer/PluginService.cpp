#include "PluginService.h"
#include "Common.h"
#include <windows.h>
PluginService::PluginService(std::string sPath)
{
	if (init_functions(sPath))
	{
		ServiceInterface *pTmp = func_ceate_plugin_template();
		if (pTmp)
		{
			pServiceIf = func_instantiate_plugin_template(pTmp);
			if (!pServiceIf)
			{
				FreeLibrary(hDll);
				hDll = NULL;
				bEnable = false;
				pTmp->destory();
				return;
			}
			else
			{
				Route_Info *ri = NULL;
				int nRouteCount = pServiceIf->route_infos(ri);
				for (int nIndexRoute = 0; nIndexRoute < nRouteCount; nIndexRoute++)
				{
					vector<string> vecPart;
					split(ri[nIndexRoute].szPath, "/", &vecPart);
					int nPartCnt = vecPart.size();

					map<string, RoutePart>::iterator itFind = mRoutes.find(ri[nIndexRoute].szOperation);
					RoutePart *pTmp = NULL;
					if (itFind != mRoutes.end())
						pTmp = &(itFind->second);
					else

					for (int nIndex = 0; nIndex < nPartCnt; nIndex++)
					{
						if (vecPart[nIndex].compare("") == 0)
							continue;
						pTmp = pTmp->insert(vecPart[nIndex]);
					}
					if (pTmp != &(itFind->second))
						pTmp->set_create_index(ri[nIndexRoute].nIndex);

				}
				bEnable = true;
			}
		}
		else
		{
			FreeLibrary(hDll);
			hDll = NULL;
			bEnable = false;
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
		func_create_business = (FunCreateBusiness)GetProcAddress(hDll, "create_business");
		if (!func_create_business)
		{
			FreeLibrary(hDll); hDll = NULL;
			return false;
		}

		func_ceate_plugin_template = (FunCreatePluginTemplate)GetProcAddress(hDll, "create_plugin_template");
		if (!func_ceate_plugin_template)
		{
			FreeLibrary(hDll); hDll = NULL;
			return false;
		}

		func_instantiate_plugin_template = (FunInstantiatePluginTemplate)GetProcAddress(hDll, "instantiate_plugin_template");
		if (!func_instantiate_plugin_template)
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

int PluginService::parse_path(const char *szOperator, const char *szPath, vector<string> &vecParameters)
{
	return -1;
}