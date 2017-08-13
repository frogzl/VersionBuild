#pragma once
#include "Task.h"
#include "PluginTask.h"
#include <map>
#include <string>
using namespace std;
class PluginCenter
{
public:
	static void load_task_plugins();
	static void install_task_plugin(const char *szPluginID, const char *szPluginVersion);
	static void uninstall_task_plugin(const char *szPluginID, const char *szPluginVersion);
	static Task* parse_task_path(const char *szPath);
	static void free_task(Task *&pTask);
	static void destory();
private:
	static string generate_plugin_key(const char *szPluginID, const char *szPluginVersion);
	static bool analysis_task_path(const char *szPath, Task *pTask);
	static PluginTask* enum_task_plugin(const char *szPluginID, const char *szPluginVersion);
	static void enum_dll_path(int nLayer, string sPath, int nDepth, map<string, string> &mDll);
private:
	static HANDLE hPluginTaskMutex;
	static map<string, PluginTask*> mPluginTask;
};