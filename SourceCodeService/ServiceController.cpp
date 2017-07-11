#include "stdafx.h"
#include "ServiceController.h"

ServiceController::ServiceController()
{
	riRouteInfos = NULL;
	nRouteInfoCnt = 0;
	nRouteInfoIndex = 0;
	register_http_routes();
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

bool ServiceController::register_http_get(const char *szPath, const char *szBusinessName)
{
	return register_http_route(szPath, szBusinessName, "get");
}

bool ServiceController::register_http_http_post(const char *szPath, const char *szBusinessName)
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

bool ServiceController::init_route_count(int nCount)
{
	riRouteInfos = new Route_Info[nCount];
	nRouteInfoCnt = nCount;
	nRouteInfoIndex = 0;
}

bool ServiceController::register_http_route(const char *szPath, const char *szBusinessName, const char *szOperation)
{
	if (nRouteInfoCnt < nRouteInfoIndex)
	{
		riRouteInfos[nRouteInfoIndex].nIndex = nRouteInfoIndex;
		riRouteInfos[nRouteInfoIndex].szPath = szPath;
		riRouteInfos[nRouteInfoIndex].szBusinessName = szBusinessName;
		riRouteInfos[nRouteInfoIndex].szoperation = szOperation;
	}
	nRouteInfoIndex++;
}
