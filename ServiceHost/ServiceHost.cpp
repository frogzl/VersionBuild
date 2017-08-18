// ServiceHost.cpp : ���� DLL Ӧ�ó���ĵ���������
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
		pService->register_service_name("MasterTask");
		pService->register_service_unique_id("9f9c1098-a202-4d32-ab82-a960631db67c");
		pService->register_service_version("1");

		// �������
		pService->register_service_route("/host", Http_Operator_Post, RouteCallBackSet::create_host);

		// ��ѯ����
		pService->register_service_route("/host", Http_Operator_Get, RouteCallBackSet::query_host);
		pService->register_service_route("/host/{id}", Http_Operator_Get, RouteCallBackSet::query_host);

		// ɾ������
		pService->register_service_route("/host/{id}/status/delete", Http_Operator_Post, RouteCallBackSet::delete_host);

		// �޸�����
		pService->register_service_route("/host/{id}/status/modify", Http_Operator_Post, RouteCallBackSet::modify_host);

		// ��ѯ��ִ�н�ɫ
		pService->register_service_route("/executable-role", Http_Operator_Get, RouteCallBackSet::query_executable_role);
		pService->register_service_route("/executable-role/{id}", Http_Operator_Get, RouteCallBackSet::query_executable_role);

		// ��ӿ�ִ�н�ɫ�Ĳ�����Ϣ
		pService->register_service_route("/deployment_information/executable_role", Http_Operator_Post, RouteCallBackSet::create_executable_role_deployment_information);

		// ��ѯ��ִ�н�ɫ�Ĳ�����Ϣ
		pService->register_service_route("/deployment_information/executable_role", Http_Operator_Get, RouteCallBackSet::query_executable_role_deployment_information);
		pService->register_service_route("/deployment_information/executable_role/{id}", Http_Operator_Get, RouteCallBackSet::query_executable_role_deployment_information);

		// �޸Ŀ�ִ�н�ɫ�Ĳ�����Ϣ
		pService->register_service_route("/deployment_information/executable_role/{id}/status/modify", Http_Operator_Post, RouteCallBackSet::modify_executable_role_deployment_information);

		// ɾ����ִ�н�ɫ�Ĳ�����Ϣ
		pService->register_service_route("/deployment_information/executable_role/{id}/status/delete", Http_Operator_Post, RouteCallBackSet::delete_executable_role_deployment_information);

		return instantiate_plugin_template(pService);
	}
	else
		return NULL;
}