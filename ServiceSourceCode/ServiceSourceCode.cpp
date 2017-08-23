// ServiceSourceCode.cpp : 定义 DLL 应用程序的导出函数。
//

#include "MicroServicePlugin.h"
#include "RouteCallBackSet.h"

// 这是导出函数的一个示例。
ServiceInterface* produce_one()
{
	static bool bFirst = true;
	if (bFirst)
	{
		bFirst = false;

		ServiceInterface* pService = create_plugin_template();
		pService->register_service_name("SourceCode");
		pService->register_service_unique_id("e2cb8547-7aa0-4fe0-bad0-0f974d9270c6");
		pService->register_service_version("1");

		// 添加源码记录
		pService->register_service_route("/source-code", Http_Operator_Post, RouteCallBackSet::sourcecode_query);

		// 添加构建规则
		pService->register_service_route("/source-code/{id}/build-rule", Http_Operator_Post, RouteCallBackSet::sourcecode_query);

		// 添加构建规则的依赖源码项目
		pService->register_service_route("/source-code/{id}/build-rule/{id}/depends", Http_Operator_Post, RouteCallBackSet::sourcecode_query);

		// 添加构建结果
		pService->register_service_route("/source-code/{id}/build-rule/{id}/build-result", Http_Operator_Post, RouteCallBackSet::sourcecode_query);


		return instantiate_plugin_template(pService);
	}
	else
		return NULL;
}