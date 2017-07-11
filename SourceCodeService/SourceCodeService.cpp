// SourceCodeService.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ServiceController.h"
// 这是导出函数的一个示例。
ServiceController sc;
string service_route_infos()
{
	return sc.route_infos();
}

string service_unique_id()
{
	return sc.unique_id();
}

string service_name()
{
	return sc.name();
}

string service_version()
{
	return sc.version();
}

string service_dispatch_by_route_path(char *szRoutePath, char *sz, ServiceController::Request_Data &inData, ServiceController::Respond_Data &outData)
{
	return sc.dispatch_by_route_path(szRoutePath, sz, inData, outData);
}