#pragma once
#include "Common.h"
#include <windows.h>
#include "TaskInterface.h"
#include <vector>
#include <map>
#include <string>
using namespace std;
typedef TaskInterface* (*FUNCProduceOne)();
class PluginTask
{
public:
	PluginTask(std::string sPath);
	~PluginTask();

	const char* unique_id() { return pTaskIf->unique_id(); }
	const char* name() { return pTaskIf->name(); }
	const char* version() { return pTaskIf->version(); }
	const char* library_version() { return pTaskIf->library_version(); }
	TaskData* create_data() { return pTaskIf->create_data(); }
	int route_infos(Task_Route_Info *&routeInfos) { return pTaskIf->route_infos(routeInfos); }
	bool enable() { return bEnable; }
	bool dispatch(int nIndex, TaskData *pD);
	int parse_path(const char *szPath);
private:
	bool init_functions(string &sPath);
private:
	TaskInterface *pTaskIf;
	FUNCProduceOne func_produce_one;
	bool bEnable;

	HANDLE hRouteMutex;
	map<string, int> mRoutes;
	HMODULE hDll;
};

