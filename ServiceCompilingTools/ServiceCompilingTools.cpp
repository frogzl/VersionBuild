// ServiceCompilingTools.cpp : 定义 DLL 应用程序的导出函数。
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
		pService->register_service_name("CompilingTools");
		pService->register_service_unique_id("3b3595eb-6e88-4339-a80f-fb1bf51bed5b");
		pService->register_service_version("1");

		// 添加新的编译工具模板
		pService->register_service_route("/compiling-tool", Http_Operator_Post, RouteCallBackSet::create_compiling_tool_template);
	
		// 查询编译工具模板
		pService->register_service_route("/compiling-tool", Http_Operator_Get, RouteCallBackSet::query_compiling_tool_template);
		pService->register_service_route("/compiling-tool/{id}", Http_Operator_Get, RouteCallBackSet::query_compiling_tool_template);

		// 添加新的编译工具实例
		pService->register_service_route("/compiling-tool-instance", Http_Operator_Post, RouteCallBackSet::create_compiling_tool_instance);

		// 查询编译工具模板
		pService->register_service_route("/compiling-tool-instance", Http_Operator_Get, RouteCallBackSet::query_compiling_tool_instance);
		pService->register_service_route("/compiling-tool-instance/{id}", Http_Operator_Get, RouteCallBackSet::query_compiling_tool_instance);

		return instantiate_plugin_template(pService);
	}
	else
		return NULL;
}