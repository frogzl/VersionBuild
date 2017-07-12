#include "stdafx.h"
#include "ServiceController.h"

ServiceController::ServiceController()
{
	riRouteInfos = NULL;
	nRouteInfoCnt = 0;
	nRouteInfoIndex = 0;
}

ServiceController::~ServiceController()
{
	delete [] riRouteInfos;
	riRouteInfos = NULL;
	nRouteInfoCnt = 0;
	nRouteInfoIndex = 0;
}

int ServiceController::route_infos(Route_Info *&routeInfos)
{
	return 0;
}

const char* ServiceController::unique_id()
{
	return szServiceUniqueId;
}

const char* ServiceController::name()
{
	return szServiceName;
}

const char* ServiceController::version()
{
	return szServiceVersion;
}

string ServiceController::dispatch_by_route_path(int nIndex, Request_Data &inData, Respond_Data &outData)
{
	return "";
}

bool ServiceController::init_route_count(int nCount)
{
	riRouteInfos = new Route_Info[nCount];
	memset(riRouteInfos, 0, nCount * sizeof(Route_Info));
	nRouteInfoCnt = nCount;
	nRouteInfoIndex = 0;
}

bool ServiceController::register_http_get(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "get");
}

bool ServiceController::register_http_post(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "post");
}

bool ServiceController::register_http_head(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "head");
}

bool ServiceController::register_http_put(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "put");
}

bool ServiceController::register_http_delete(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "delete");
}

bool ServiceController::register_http_trace(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "trace");
}

bool ServiceController::register_http_options(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "options");
}

bool ServiceController::register_service_name(const char *szName)
{
	szServiceName = szName;
	return true;
}

bool ServiceController::register_service_unique_id(const char *szID)
{
	szServiceUniqueId = szID;
	return true;
}


bool ServiceController::register_service_version(const char *szVersion)
{
	szServiceVersion = szVersion;
	return true;
}

bool ServiceController::register_http_route(const char *szPath, const char *szBusinessName, const char *szOperation)
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
