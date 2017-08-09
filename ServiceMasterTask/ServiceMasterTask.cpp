// ServiceMasterTask.cpp : 定义 DLL 应用程序的导出函数。
//

#include "MicroServicePlugin.h"

ServiceInterface* produce_one()
{
	ServiceInterface* pService = create_plugin_template();
	pService->register_service_name("MasterTask");
	pService->register_service_unique_id("ffeafe48-3c6e-49d8-a85c-783167eada00");
	pService->register_service_version("1");
	//	pService->register_service_route("/task/master/create", Http_Operator_Get, RouteCallBackSet::sourcecode_query);
	//	pService->register_service_route("/task/master/query", Http_Operator_Post, RouteCallBackSet::sourcecode_create);
	//	pService->register_service_route("/task/master/delete", Http_Operator_Post, RouteCallBackSet::sourcecode_modify);
	//	pService->register_service_route("/task/master/work/finish", Http_Operator_Post, RouteCallBackSet::sourcecode_modify);
	return instantiate_plugin_template(pService);
}