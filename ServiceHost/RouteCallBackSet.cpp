#include "RouteCallBackSet.h"
#include "Business\CreateHost.h"
#include "Business\QueryHost.h"
#include "Business\DeleteHost.h"
#include "Business\ModifyHost.h"
#include "Business\QueryExecutableRole.h"
#include "Business\CreateExecutableRoleDeploymentInformation.h"
#include "Business\QueryExecutableRoleDeploymentInformation.h"
#include "Business\ModifyExecutableRoleDeploymentInformation.h"
#include "Business\DeleteExecutableRoleDeploymentInformation.h"

void RouteCallBackSet::create_host(ServiceData *pD)
{
	CreateHost ch(pD);
	ch.process_task();
}

void RouteCallBackSet::query_host(ServiceData *pD)
{
	QueryHost qh(pD);
	qh.process_task();
}

void RouteCallBackSet::delete_host(ServiceData *pD)
{
	DeleteHost dh(pD);
	dh.process_task();
}

void RouteCallBackSet::modify_host(ServiceData *pD)
{
	ModifyHost mh(pD);
	mh.process_task();
}

void RouteCallBackSet::query_executable_role(ServiceData *pD)
{
	QueryExecutableRole qer(pD);
	qer.process_task();
}

void RouteCallBackSet::create_executable_role_deployment_information(ServiceData *pD)
{
	CreateExecutableRoleDeploymentInformation cerdi(pD);
	cerdi.process_task();
}

void RouteCallBackSet::query_executable_role_deployment_information(ServiceData *pD)
{
	QueryExecutableRoleDeploymentInformation qerdi(pD);
	qerdi.process_task();
}

void RouteCallBackSet::modify_executable_role_deployment_information(ServiceData *pD)
{
	ModifyExecutableRoleDeploymentInformation merdi(pD);
	merdi.process_task();
}

void RouteCallBackSet::delete_executable_role_deployment_information(ServiceData *pD)
{
	DeleteExecutableRoleDeploymentInformation derdi(pD);
	derdi.process_task();
}