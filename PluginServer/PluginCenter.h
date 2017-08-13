#pragma once
#include "Service.h"
#include "PluginService.h"
#include "RoutePart.h"
#include <map>
#include <string>
using namespace std;
class PluginCenter
{
public:
	static void load_service_plugins();
	static void install_service_plugin(const char *szPluginID, const char *szPluginVersion);
	static void uninstall_service_plugin(const char *szPluginID, const char *szPluginVersion);
	static Service* parse_service_path(const char *szOperator, const char *szPath);
	static void free_service(Service *&pService);
	static void destory();
private:
	static string generate_plugin_key(const char *szPluginID, const char *szPluginVersion);
	static bool analysis_service_path(const char *szOperator, const char *szPath, Service *pService);
	static PluginService* enum_service_plugin(const char *szPluginID, const char *szPluginVersion);
	static void enum_dll_path(int nLayer, string sPath, int nDepth, map<string, string> &mDll);
private:
	static HANDLE hPluginServiceMutex;
	static map<string, PluginService*> mPluginService;
};