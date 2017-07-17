// SourceCodeService.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Service.h"
#include "Business/SourceCodeBuild.h"
#include "Business/SourceCodeCreate.h"
// 这是导出函数的一个示例。
ServiceInterface* produce_one()
{
	ServiceInterface* pService = create_plugin_template();
	pService->register_service_name("SourceCode");
	pService->register_service_unique_id("{e2cb8547-7aa0-4fe0-bad0-0f974d9270c6}");
	pService->register_service_version("1");
	pService->register_http_route("/sourcecode/query", Http_Operator_Get, BUSINESS(SourceCodeQuery));
	pService->register_http_route("/sourcecode/create", Http_Operator_Post, BUSINESS(SourceCodeCreate));
	pService->register_http_route("/sourcecode/modify", Http_Operator_Post, BUSINESS(SourceCodeModify));
	pService->register_http_route("/sourcecode/deploy", Http_Operator_Post, BUSINESS(SourceCodeDeploy));
	pService->register_http_route("/sourcecode/build", Http_Operator_Post, BUSINESS(SourceCodeBuild));
	pService->register_http_route("/sourcecode/delete", Http_Operator_Post, BUSINESS(SourceCodeDelete));
	return instantiate_plugin_template(pService);
}