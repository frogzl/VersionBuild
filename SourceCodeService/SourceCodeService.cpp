// SourceCodeService.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Service.h"
#include "Business/SourceCodeBuild.h"
#include "Business/SourceCodeCreate.h"
// 这是导出函数的一个示例。
ServiceInterface* produce_one()
{
	register_service_name("SourceCode");
	register_service_unique_id("{e2cb8547-7aa0-4fe0-bad0-0f974d9270c6}");
	register_service_version("1");
	register_service_business_factory(new BusinessFactory());

	init_route_count(6);
	register_http_get("/sourcecode/query", "SourceCodeQuery");
	register_http_post("/sourcecode/create", "SourceCodeCreate");
	register_http_post("/sourcecode/modify", "SourceCodeModify");
	register_http_post("/sourcecode/deploy", "SourceCodeDeploy");
	register_http_post("/sourcecode/build", "SourceCodeBuild");
	register_http_post("/sourcecode/delete", "SourceCodeDelete");
	return new Service();
}