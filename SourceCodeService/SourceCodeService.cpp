// SourceCodeService.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ServiceController.h"
// ���ǵ���������һ��ʾ����
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