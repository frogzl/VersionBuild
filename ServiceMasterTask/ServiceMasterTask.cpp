// ServiceMasterTask.cpp : 定义 DLL 应用程序的导出函数。
//

#include "MicroServicePlugin.h"
#include "RouteCallBackSet.h"
ServiceInterface* produce_one()
{
	ServiceInterface* pService = create_plugin_template();
	pService->register_service_name("MasterTask");
	pService->register_service_unique_id("ffeafe48-3c6e-49d8-a85c-783167eada00");
	pService->register_service_version("1");
	pService->register_service_route("/task/{id}", Http_Operator_Get, RouteCallBackSet::query_task);
	pService->register_service_route("/task", Http_Operator_Get, RouteCallBackSet::query_task);
	pService->register_service_route("/task", Http_Operator_Post, RouteCallBackSet::create_task);
	pService->register_service_route("/task/{id}/finish", Http_Operator_Post, RouteCallBackSet::finish_task);
	pService->register_service_route("/task/{id}", Http_Operator_Delete, RouteCallBackSet::delete_task);
	return instantiate_plugin_template(pService);
}