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

		// 新建-----------------------------------------------------------
		// 添加源码记录
		pService->register_service_route("/source-code", Http_Operator_Post, RouteCallBackSet::add_source_code);

		// 添加构建规则
		pService->register_service_route("/source-code/{id}/build-rule", Http_Operator_Post, RouteCallBackSet::add_build_rule);

		// 添加构建规则的依赖源码项目
		pService->register_service_route("/source-code/{id}/build-rule/{id}/depends", Http_Operator_Post, RouteCallBackSet::add_build_rule_depends);

		// 添加构建结果
		pService->register_service_route("/source-code/{id}/build-rule/{id}/build-result", Http_Operator_Post, RouteCallBackSet::add_build_rule_result);

		// 查询-----------------------------------------------------------
		// 查询源码记录
		pService->register_service_route("/source-code", Http_Operator_Get, RouteCallBackSet::query_source_code);
		pService->register_service_route("/source-code/{id}", Http_Operator_Get, RouteCallBackSet::query_source_code);

		// 查询构建规则
		pService->register_service_route("/source-code/{id}/build-rule", Http_Operator_Get, RouteCallBackSet::query_build_rule);
		pService->register_service_route("/source-code/{id}/build-rule/{id}", Http_Operator_Get, RouteCallBackSet::query_build_rule);

		// 查询构建规则的依赖源码项目
		pService->register_service_route("/source-code/{id}/build-rule/{id}/depends", Http_Operator_Get, RouteCallBackSet::query_build_rule_depends);
		pService->register_service_route("/source-code/{id}/build-rule/{id}/depends/{id}", Http_Operator_Get, RouteCallBackSet::query_build_rule_depends);

		// 查询构建结果
		pService->register_service_route("/source-code/{id}/build-rule/{id}/build-result", Http_Operator_Get, RouteCallBackSet::query_build_rule_result);
		pService->register_service_route("/source-code/{id}/build-rule/{id}/build-result/{id}", Http_Operator_Get, RouteCallBackSet::query_build_rule_result);

		// 更新-----------------------------------------------------------
		// 更新源码记录
		pService->register_service_route("/source-code/{id}", Http_Operator_Put, RouteCallBackSet::update_source_code);

		// 更新构建规则
		pService->register_service_route("/source-code/{id}/build-rule/{id}", Http_Operator_Put, RouteCallBackSet::update_build_rule);

		// 更新构建规则的依赖源码项目
		pService->register_service_route("/source-code/{id}/build-rule/{id}/depend/{id}", Http_Operator_Put, RouteCallBackSet::update_build_rule_depends);

		// 更新构建结果
		pService->register_service_route("/source-code/{id}/build-rule/{id}/build-result/{id}", Http_Operator_Put, RouteCallBackSet::update_build_rule_result);

		// 编译-----------------------------------------------------------
		// 编译源码
		pService->register_service_route("/source-code/{id}/state/auto-build", Http_Operator_Put, RouteCallBackSet::auto_build_source_code);
		pService->register_service_route("/source-code/{id}/state/build", Http_Operator_Put, RouteCallBackSet::build_source_code);

		return instantiate_plugin_template(pService);
	}
	else
		return NULL;
}