// ServiceSourceCode.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "MicroServicePlugin.h"
#include "RouteCallBackSet.h"

// ���ǵ���������һ��ʾ����
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

		// �½�-----------------------------------------------------------
		// ���Դ���¼
		pService->register_service_route("/source-code", Http_Operator_Post, RouteCallBackSet::add_source_code);

		// ��ӹ�������
		pService->register_service_route("/source-code/{id}/build-rule", Http_Operator_Post, RouteCallBackSet::add_build_rule);

		// ��ӹ������������Դ����Ŀ
		pService->register_service_route("/source-code/{id}/build-rule/{id}/depends", Http_Operator_Post, RouteCallBackSet::add_build_rule_depends);

		// ��ӹ������
		pService->register_service_route("/source-code/{id}/build-rule/{id}/build-result", Http_Operator_Post, RouteCallBackSet::add_build_rule_result);

		// ��ѯ-----------------------------------------------------------
		// ��ѯԴ���¼
		pService->register_service_route("/source-code", Http_Operator_Get, RouteCallBackSet::query_source_code);
		pService->register_service_route("/source-code/{id}", Http_Operator_Get, RouteCallBackSet::query_source_code);

		// ��ѯ��������
		pService->register_service_route("/source-code/{id}/build-rule", Http_Operator_Get, RouteCallBackSet::query_build_rule);
		pService->register_service_route("/source-code/{id}/build-rule/{id}", Http_Operator_Get, RouteCallBackSet::query_build_rule);

		// ��ѯ�������������Դ����Ŀ
		pService->register_service_route("/source-code/{id}/build-rule/{id}/depends", Http_Operator_Get, RouteCallBackSet::query_build_rule_depends);
		pService->register_service_route("/source-code/{id}/build-rule/{id}/depends/{id}", Http_Operator_Get, RouteCallBackSet::query_build_rule_depends);

		// ��ѯ�������
		pService->register_service_route("/source-code/{id}/build-rule/{id}/build-result", Http_Operator_Get, RouteCallBackSet::query_build_rule_result);
		pService->register_service_route("/source-code/{id}/build-rule/{id}/build-result/{id}", Http_Operator_Get, RouteCallBackSet::query_build_rule_result);

		// ����-----------------------------------------------------------
		// ����Դ���¼
		pService->register_service_route("/source-code/{id}", Http_Operator_Put, RouteCallBackSet::update_source_code);

		// ���¹�������
		pService->register_service_route("/source-code/{id}/build-rule/{id}", Http_Operator_Put, RouteCallBackSet::update_build_rule);

		// ���¹������������Դ����Ŀ
		pService->register_service_route("/source-code/{id}/build-rule/{id}/depend/{id}", Http_Operator_Put, RouteCallBackSet::update_build_rule_depends);

		// ���¹������
		pService->register_service_route("/source-code/{id}/build-rule/{id}/build-result/{id}", Http_Operator_Put, RouteCallBackSet::update_build_rule_result);

		// ����-----------------------------------------------------------
		// ����Դ��
		pService->register_service_route("/source-code/{id}/state/auto-build", Http_Operator_Put, RouteCallBackSet::auto_build_source_code);
		pService->register_service_route("/source-code/{id}/state/build", Http_Operator_Put, RouteCallBackSet::build_source_code);

		return instantiate_plugin_template(pService);
	}
	else
		return NULL;
}