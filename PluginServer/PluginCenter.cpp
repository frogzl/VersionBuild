#include "PluginCenter.h"
#include <Windows.h>
#include <io.h>
#include "Common.h"
void PluginCenter::load_service_plugins()
{
	char szPath[255];
	GetModuleFileNameA(NULL, szPath, 255);
	std::string sPath(szPath);
	int nPos = (int)sPath.find("PluginServer.exe", 0);
	int nNameSize = sizeof("PluginServer.exe");
	sPath.erase(nPos, nNameSize - 1);
	std::string sPluginServicePath = sPath + "MicroServicePlugins";

	_finddata_t fd;
	intptr_t pf = _findfirst("e:/*.*", &fd);
	while (!_findnext(pf, &fd))
	{
		std::string sDll = sPluginServicePath + " \\" + fd.name;
		PluginService *pPlugin = new PluginService(sDll);
		if (pPlugin->enable())
		{
			Route_Info *routeInfos = NULL;
			int nRouteCnt = pPlugin->route_infos(routeInfos);
			for (int nIndex = 0; nIndex < nRouteCnt; nIndex++)
				append_route(pPlugin->unique_id(), pPlugin->version(), routeInfos[nIndex]);
		}
		else
		{
			delete pPlugin;
			continue;
		}
	}
	_findclose(pf);
}

void PluginCenter::load_task_plugins()
{
	char szPath[255];
	GetModuleFileNameA(NULL, szPath, 255);
	std::string sPath(szPath);
	int nPos = (int)sPath.find("PluginServer.exe", 0);
	int nCount = sizeof("PluginServer.exe");
	sPath.erase(nPos, nCount - 1);
	std::string sPluginTaskPath = sPath + "MicroTaskPlugins";

}

void PluginCenter::install_service_plugin(const char *szPluginID, const char *szPluginVersion)
{

}

void PluginCenter::install_task_plugin(const char *szPluginID, const char *szPluginVersion)
{

}

void PluginCenter::uninstall_service_plugin(const char *szPluginID, const char *szPluginVersion)
{

}

void PluginCenter::uninstall_task_plugin(const char *szPluginID, const char *szPluginVersion)
{

}

Service* PluginCenter::parse_service_path(const char *szOperator, const char *szPath)
{
	Service *pService = new Service();
	if (analysis_service_path(szOperator, szPath, pService))
		return pService;
	delete pService;
	return 0;
}

Task* PluginCenter::parse_task_path()
{
	return 0;
}

void PluginCenter::free_service(Service *&pService)
{
	delete pService;
	pService = NULL;
}

void PluginCenter::free_task(Task *&pTask)
{

}

bool PluginCenter::analysis_service_path(const char *szOperator, const char *szPath, Service *pService)
{
	std::vector<std::string> vecItem;
	split(szPath, "/", vecItem);
	if (vecItem.size() == 0)
		return false;
	if (vecItem[0].compare("service") != 0)
		return false;

	PluginService *pPlugin = enum_service_plugin(szOperator, vecItem[1].c_str(), vecItem[2].c_str());
	if (pPlugin)
	{
		pService->setCreateIndex(parse_service_path(3, vecItem, pService->data()->request_data().mParameters));
		pService->setPlugin(pPlugin);
	}
}

void PluginCenter::append_route(const char* szUniqueID, const char* szVersion, Route_Info &ri)
{

}

PluginService* PluginCenter::enum_service_plugin(const char *szOperator, const char *szPluginID, const char *szPluginVersion)
{

}

int PluginCenter::parse_service_path(int nStartIndex, std::vector<std::string> &vecItem, std::map<int, std::string>&mParam)
{

}