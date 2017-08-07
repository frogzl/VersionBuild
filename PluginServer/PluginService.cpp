#include "PluginService.h"
#include <windows.h>
PluginService::PluginService(std::string sPath)
{
	HMODULE hDll = LoadLibraryA(sPath.c_str());
	if (hDll)
	{
		func_create_business = (FunCreateBusiness)GetProcAddress(hDll, "create_business");
		if (!func_create_business)
		{
			FreeLibrary(hDll);
			hDll = NULL;
			bEnable = false;
			return;
		}

		func_ceate_plugin_template = (FunCreatePluginTemplate)GetProcAddress(hDll, "create_plugin_template");
		if (!func_ceate_plugin_template)
		{
			FreeLibrary(hDll);
			hDll = NULL;
			bEnable = false;
			return;
		}

		func_instantiate_plugin_template = (FunInstantiatePluginTemplate)GetProcAddress(hDll, "instantiate_plugin_template");
		if (!func_instantiate_plugin_template)
		{
			FreeLibrary(hDll);
			hDll = NULL;
			bEnable = false;
			return;
		}
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
			bEnable = true;
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

bool PluginService::dispatch(int nIndex, ServiceData *pD)
{
	return pServiceIf->dispatch_by_route_path(nIndex, pD);
}

int PluginService::parse_path(const char *szOperator, const char *szPath, vector<string> &vecParameters)
{

}