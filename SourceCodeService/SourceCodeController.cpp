#include "StdAfx.h"
#include "SourceCodeController.h"


SourceCodeController::SourceCodeController()
{
	register_service_name("SourceCode");
	register_service_unique_id("{e2cb8547-7aa0-4fe0-bad0-0f974d9270c6}");
	register_service_version("1");

	init_route_count(6);
	register_http_get("/sourcecode/query", "SourceCodeQuery");
	register_http_post("/sourcecode/create", "SourceCodeCreate");
	register_http_post("/sourcecode/modify", "SourceCodeModify");
	register_http_post("/sourcecode/deploy", "SourceCodeDeploy");
	register_http_post("/sourcecode/build", "SourceCodeBuild");
	register_http_post("/sourcecode/delete", "SourceCodeDelete");
}


SourceCodeController::~SourceCodeController()
{
}