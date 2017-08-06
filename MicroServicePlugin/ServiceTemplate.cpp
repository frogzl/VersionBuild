#include "ServiceTemplate.h"

ServiceTemplate::ServiceTemplate()
{
	nRouteCount = -1;
	riRouteInfos = NULL;
	fpRoutesProcess = NULL;
	omObjectMode = enTemplate;
	pVecTmpRI = new std::vector<Route_Info>();
	pVecTmpFP = new std::vector<FuncProcess>();
}

ServiceTemplate::~ServiceTemplate()
{
	if (fpRoutesProcess)
		delete [] fpRoutesProcess;
	if (riRouteInfos)
		delete [] riRouteInfos;

	if (pVecTmpRI)
		delete pVecTmpRI;
	if (pVecTmpFP)
		delete pVecTmpFP;

	pVecTmpRI = NULL;
	pVecTmpFP = NULL;
	fpRoutesProcess = NULL;
	riRouteInfos = NULL;
}

void ServiceTemplate::destory()
{
	delete this;
}

int ServiceTemplate::route_infos(Route_Info *&routeInfos)
{
	return 0;
}

const char* ServiceTemplate::unique_id()
{
	return szServiceUniqueId;
}

const char* ServiceTemplate::name()
{
	return szServiceName;
}

const char* ServiceTemplate::version()
{
	return szServiceVersion;
}

const char* ServiceTemplate::library_version()
{
	return "0.1";
}

bool ServiceTemplate::dispatch_by_route_path(int nIndex, ServiceData *pD)
{
	if (nIndex >= 0 && nIndex < nRouteCount)
	{
		fpRoutesProcess[nIndex](pD);
		return true;
	}
	else
		return false;
}

bool ServiceTemplate::register_service_name(const char *szName)
{
	szServiceName = szName;
	return true;
}

bool ServiceTemplate::register_service_unique_id(const char *szID)
{
	szServiceUniqueId = szID;
	return true;
}


bool ServiceTemplate::register_service_version(const char *szVersion)
{
	szServiceVersion = szVersion;
	return true;
}

bool ServiceTemplate::register_service_route(const char *szPath, const char *szOperation, FuncProcess pCallBack)
{
	Route_Info ri;
	ri.nIndex = (int)pVecTmpFP->size();
	ri.szPath = szPath;
	ri.szoperation = szOperation;
	pVecTmpRI->push_back(ri);
	pVecTmpFP->push_back(pCallBack);
	return true;
}

bool ServiceTemplate::change_to_fast_mode()
{
	if (omObjectMode == enInstantiation)
		return true;
	if (pVecTmpRI->size() != pVecTmpFP->size())
		return false;

	nRouteCount = (int)pVecTmpRI->size();
	if (nRouteCount > 0)
	{
		riRouteInfos = new Route_Info[nRouteCount];
		fpRoutesProcess = new FuncProcess[nRouteCount];
		for (int nIndexRI = 0; nIndexRI < nRouteCount; nIndexRI++)
			riRouteInfos[nIndexRI] = (*pVecTmpRI)[nIndexRI];
		for (int nIndexFP = 0; nIndexFP < nRouteCount; nIndexFP++)
			fpRoutesProcess[nIndexFP] = (*pVecTmpFP)[nIndexFP];
	}
	delete pVecTmpRI;
	pVecTmpRI = NULL;

	omObjectMode = enInstantiation;
	return true;
}