#include "PluginCenter.h"
#include <io.h>
#include "Common.h"
#include <Windows.h>
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
	if (vecItem.size() < 3)
		return false;

	PluginService *pPlugin = enum_service_plugin(szOperator, vecItem[1].c_str(), vecItem[2].c_str());
	if (pPlugin)
	{
		int nCreateIndex = pPlugin->parse_path(szOperator, szPath, pService->data()->request_data().vecParameters);
		if (nCreateIndex != -1)
		{
			pService->setCreateIndex(nCreateIndex);
			pService->setPlugin(pPlugin);
			return true;
		}
		else
			return false;
	}
}

void PluginCenter::append_route(const char* szUniqueID, const char* szVersion, Route_Info &ri)
{
	string sSplit = "_";
	string sKey = szUniqueID + sSplit + szVersion + sSplit + ri.szOperation;
	map<string, RoutePart>::iterator itFind = mRoute.find(sKey);

	vector<string> vecPart;
	split(ri.szPath, "/", &vecPart);
	int nPartCnt = vecPart.size();
	if (itFind != mRoute.end())
	{
		RoutePart *pTmp = &(itFind->second);
		for (int nIndex = 0; nIndex < nPartCnt; nIndex++)
		{
			if (vecPart[nIndex].compare("") == 0)
				continue;
			pTmp = pTmp->insert(vecPart[nIndex]);
		}
		if (pTmp != &(itFind->second))
			pTmp->set_create_index(ri.nIndex);
	}
	else
	{
		RoutePart rp;
		RoutePart *pTmp = &rp;
		for (int nIndex = 0; nIndex < nPartCnt; nIndex++)
		{
			if (vecPart[nIndex].compare("") == 0)
				continue;
			pTmp = pTmp->insert(vecPart[nIndex]);
		}
		if (pTmp != &(itFind->second))
			pTmp->set_create_index(ri.nIndex);
		mRoute.insert(pair<string, RoutePart>(sKey, rp));
	}
}

PluginService* PluginCenter::enum_service_plugin(const char *szOperator, const char *szPluginID, const char *szPluginVersion)
{
	string sSplit = "_";
	string sKey = szPluginID + sSplit + szPluginVersion + sSplit + szOperator;
	map<string, RoutePart>::iterator itFind = mRoute.find(sKey);

}