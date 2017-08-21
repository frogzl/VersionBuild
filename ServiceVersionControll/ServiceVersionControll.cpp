// ServiceVersionControll.cpp : 定义 DLL 应用程序的导出函数。
//
#include "MicroServicePlugin.h"
#include "RouteCallBackSet.h"
ServiceInterface* produce_one()
{
	static bool bFirst = true;
	if (bFirst)
	{
		bFirst = false;

		ServiceInterface* pService = create_plugin_template();
		pService->register_service_name("SlaveTask");
		pService->register_service_unique_id("33ff9e34-a9a3-4d42-a84c-8ecea956354f");
		pService->register_service_version("1");

		// 查询支持那些版本控制
		pService->register_service_route("/version-tools", Http_Operator_Get, RouteCallBackSet::upload);
		pService->register_service_route("/version-tools/{id}", Http_Operator_Get, RouteCallBackSet::upload);

		// 查询支持那些版本控制产品
		pService->register_service_route("/version-tools/{id}/product", Http_Operator_Get, RouteCallBackSet::upload);
		pService->register_service_route("/version-tools/{id}/product/{id}", Http_Operator_Get, RouteCallBackSet::upload);

		return instantiate_plugin_template(pService);
	}
	else
		return NULL;
}