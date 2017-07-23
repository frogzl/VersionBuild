// ServiceSlaveTask.cpp : 定义 DLL 应用程序的导出函数。
//

#include "MicroServicePlugin.h"

ServiceInterface* produce_one()
{
	ServiceInterface* pService = create_plugin_template();
	pService->register_service_name("MasterTask");
	pService->register_service_unique_id("{cc0e7465-9c6d-4802-8786-2bafd9ef9ff4}");
	pService->register_service_version("1");
//	pService->register_http_route("/task/slave/work/start", Http_Operator_Post, RouteCallBackSet::sourcecode_query);
	return instantiate_plugin_template(pService);
}