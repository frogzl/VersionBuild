#include "ServiceTemplate.h"

ServiceTemplate::ServiceTemplate()
{
	bf = new BusinessFactory();
	pVecTemp = new vector<Route_Info>;
	riRouteInfos = NULL;
	omObjectMode = enTemplate;
}

ServiceTemplate::~ServiceTemplate()
{
	if (pVecTemp)
		delete pVecTemp;
	if (riRouteInfos)
		delete [] riRouteInfos;

	pVecTemp = NULL;
	riRouteInfos = NULL;
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

const char* ServiceTemplate::dispatch_by_route_path(int nIndex, Business::Request_Data &inData, Business::Respond_Data &outData)
{
	if (bf)
	{
		Business *pB = bf->get_business(riRouteInfos[nIndex].biBusiness.nIndex);
		if (pB)
		{
			outData = pB->do_business(inData);
			delete pB;
			pB = NULL;
		}
	}
	return "";
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

bool ServiceTemplate::register_http_route(const char *szPath, const char *szOperation, const char *szBusinessName, FuncCreate pCallBack)
{
	Route_Info ri;
	ri.nIndex = (int)pVecTemp->size();
	ri.szPath = szPath;
	ri.biBusiness.szBusinessName = szBusinessName;
	ri.biBusiness.nIndex = bf->register_business(szBusinessName, pCallBack);
	ri.szoperation = szOperation;
	pVecTemp->push_back(ri);
	return true;
}

bool ServiceTemplate::change_to_fast_mode()
{
	if (omObjectMode == enInstantiation)
		return true;

	int nCount = (int)pVecTemp->size();
	if (nCount > 0)
	{
		riRouteInfos = new Route_Info[nCount];
		for (int nIndex = 0; nIndex < nCount; nIndex++)
			riRouteInfos[nIndex] = (*pVecTemp)[nIndex];
	}
	delete pVecTemp;
	pVecTemp = NULL;

	bf->change_to_fast_mode();
	omObjectMode = enInstantiation;
	return true;
}