#include "stdafx.h"
#include "ServiceControllerTpl.h"

ServiceControllerTpl::ServiceControllerTpl()
{
	riRouteInfos = NULL;
	nRouteInfoCnt = 0;
	nRouteInfoIndex = 0;
}

ServiceControllerTpl::~ServiceControllerTpl()
{
	delete [] riRouteInfos;
	riRouteInfos = NULL;
	nRouteInfoCnt = 0;
	nRouteInfoIndex = 0;
}

int ServiceControllerTpl::route_infos(Route_Info *&routeInfos)
{
	return 0;
}

const char* ServiceControllerTpl::unique_id()
{
	return szServiceUniqueId;
}

const char* ServiceControllerTpl::name()
{
	return szServiceName;
}

const char* ServiceControllerTpl::version()
{
	return szServiceVersion;
}

string ServiceControllerTpl::dispatch_by_route_path(int nIndex, Business::Request_Data &inData, Business::Respond_Data &outData)
{
	Business *pB = bft->get_business(riRouteInfos[nIndex].szBusinessName);
	if (pB)
	{
		outData = pB->do_business(inData);
		delete pB;
		pB = NULL;
	}
	return "";
}

bool ServiceControllerTpl::init_route_count(int nCount)
{
	riRouteInfos = new Route_Info[nCount];
	memset(riRouteInfos, 0, nCount * sizeof(Route_Info));
	nRouteInfoCnt = nCount;
	nRouteInfoIndex = 0;
	return true;
}

bool ServiceControllerTpl::register_http_get(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "get");
}

bool ServiceControllerTpl::register_http_post(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "post");
}

bool ServiceControllerTpl::register_http_head(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "head");
}

bool ServiceControllerTpl::register_http_put(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "put");
}

bool ServiceControllerTpl::register_http_delete(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "delete");
}

bool ServiceControllerTpl::register_http_trace(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "trace");
}

bool ServiceControllerTpl::register_http_options(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "options");
}

bool ServiceControllerTpl::register_service_name(const char *szName)
{
	szServiceName = szName;
	return true;
}

bool ServiceControllerTpl::register_service_unique_id(const char *szID)
{
	szServiceUniqueId = szID;
	return true;
}


bool ServiceControllerTpl::register_service_version(const char *szVersion)
{
	szServiceVersion = szVersion;
	return true;
}

bool ServiceControllerTpl::register_http_route(const char *szPath, const char *szBusinessName, const char *szOperation)
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
