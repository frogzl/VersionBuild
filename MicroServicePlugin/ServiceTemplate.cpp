#include "ServiceTemplate.h"

ServiceTemplate::ServiceTemplate()
{
	bf = new BusinessFactory();
	riRouteInfos = NULL;
	nRouteInfoCnt = 0;
	nRouteInfoIndex = 0;
}

ServiceTemplate::~ServiceTemplate()
{
	delete [] riRouteInfos;
	riRouteInfos = NULL;
	nRouteInfoCnt = 0;
	nRouteInfoIndex = 0;
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
		Business *pB = bf->get_business(riRouteInfos[nIndex].szBusinessName);
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

bool ServiceTemplate::init_route_count(int nCount)
{
	riRouteInfos = new Route_Info[nCount];
	memset(riRouteInfos, 0, nCount * sizeof(Route_Info));
	nRouteInfoCnt = nCount;
	nRouteInfoIndex = 0;
	return true;
}

bool ServiceTemplate::register_http_route(const char *szPath, const char *szBusinessName, const char *szOperation)
{
	bool bRet = false;
	if (nRouteInfoCnt < nRouteInfoIndex)
	{
		riRouteInfos[nRouteInfoIndex].nIndex = nRouteInfoIndex;
		riRouteInfos[nRouteInfoIndex].szPath = szPath;
		riRouteInfos[nRouteInfoIndex].szBusinessName = szBusinessName;
		riRouteInfos[nRouteInfoIndex].szoperation = szOperation;
		bRet = true;
	}
	nRouteInfoIndex++;
	return bRet;
}

bool ServiceTemplate::init_business_count(int nCount)
{
	return bf->init_business_count(nCount);
}

bool ServiceTemplate::register_service_business(const char *szBusinessName, FuncCreate pCallBack)
{
//	bf->register_business(szBusinessName, pCallBack);
	return true;
}