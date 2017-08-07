#pragma once
#include "Service.h"
#include "Task.h"
#include "PluginService.h"
#include "PluginTask.h"
#include "RoutePart.h"
class PluginCenter
{
public:
	static void load_service_plugins();
	static void load_task_plugins();
	static void install_service_plugin(const char *szPluginID, const char *szPluginVersion);
	static void install_task_plugin(const char *szPluginID, const char *szPluginVersion);
	static void uninstall_service_plugin(const char *szPluginID, const char *szPluginVersion);
	static void uninstall_task_plugin(const char *szPluginID, const char *szPluginVersion);
	static Service* parse_service_path(const char *szOperator, const char *szPath);
	static Task* parse_task_path();
	static void free_service(Service *&pService);
	static void free_task(Task *&pTask);
private:
	static bool analysis_service_path(const char *szOperator, const char *szPath, Service *pService);
	static PluginService* enum_service_plugin(const char *szOperator, const char *szPluginID, const char *szPluginVersion);
	static void append_route(const char* szUniqueID, const char* szVersion, Route_Info &ri);
private:
	static map<string, RoutePart> mRoute;
};