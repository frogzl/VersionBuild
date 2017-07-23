// ServiceSourceCode.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "MicroServicePlugin.h"
#include "RouteCallBackSet.h"

// ���ǵ���������һ��ʾ����
ServiceInterface* produce_one()
{
	ServiceInterface* pService = create_plugin_template();
	pService->register_service_name("SourceCode");
	pService->register_service_unique_id("{e2cb8547-7aa0-4fe0-bad0-0f974d9270c6}");
	pService->register_service_version("1");
	pService->register_service_route("/sourcecode/query", Http_Operator_Get, RouteCallBackSet::sourcecode_query);
	pService->register_service_route("/sourcecode/create", Http_Operator_Post, RouteCallBackSet::sourcecode_create);
	pService->register_service_route("/sourcecode/modify", Http_Operator_Post, RouteCallBackSet::sourcecode_modify);
	pService->register_service_route("/sourcecode/deploy", Http_Operator_Post, RouteCallBackSet::sourcecode_deploy);
	pService->register_service_route("/sourcecode/build", Http_Operator_Post, RouteCallBackSet::sourcecode_build);
	pService->register_service_route("/sourcecode/delete", Http_Operator_Post, RouteCallBackSet::sourcecode_delete);
	return instantiate_plugin_template(pService);
}