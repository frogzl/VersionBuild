#pragma once
#include "Common.h"
#include <windows.h>
#include "ServiceInterface.h"
#include "RoutePart.h"
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef ServiceInterface* (*FUNCProduceOne)();

class PluginService
{
public:
	PluginService(std::string sPath);
	~PluginService();

	const char* unique_id() { return pServiceIf->unique_id(); }
	const char* name() { return pServiceIf->name(); }
	const char* version() { return pServiceIf->version(); }
	const char* library_version() { return pServiceIf->library_version(); }
	ServiceData* create_data() { return pServiceIf->create_data(); }
	int route_infos(Route_Info *&routeInfos) { return pServiceIf->route_infos(routeInfos); }
	bool enable() { return bEnable; }
	bool init_functions(string &sPath);
	bool dispatch(int nIndex, ServiceData *pD);
	int parse_path(const char *szOperation, const char *szPath, vector<string> &vecParameters);
private:
	ServiceInterface *pServiceIf;
	FUNCProduceOne func_produce_one;
	bool bEnable;

	HANDLE hRouteMutex;
	map<string, RoutePart> mRoutes;
	HMODULE hDll;
};