#pragma once
#include "ServiceInterface.h"
#include <string>

typedef ServiceData* (*FunCreateBusiness)();
typedef ServiceInterface* (*FunCreatePluginTemplate)();
typedef ServiceInterface* (*FunInstantiatePluginTemplate)(ServiceInterface *pInterface);
class PluginService
{
public:
	PluginService(std::string sPath);
	~PluginService();

	const char* unique_id() { return pServiceIf->unique_id(); }
	const char* name() { return pServiceIf->name(); }
	const char* version() { return pServiceIf->version(); }
	const char* library_version() { return pServiceIf->library_version(); }
	int route_infos(Route_Info *&routeInfos) { return pServiceIf->route_infos(routeInfos); }

	bool enable() { return bEnable; }
	bool dispatch(int nIndex, ServiceData *pD);
private:
	ServiceInterface *pServiceIf;
	FunCreateBusiness func_create_business;
	FunCreatePluginTemplate func_ceate_plugin_template;
	FunInstantiatePluginTemplate func_instantiate_plugin_template;
	bool bEnable;
};

