// ServiceSlaveStorage.cpp : ���� DLL Ӧ�ó���ĵ���������
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
		pService->register_service_name("SlaveStorage");
		pService->register_service_unique_id("6b59871e-274e-43ab-ab08-6cedcd60cdd9");
		pService->register_service_version("1");

		// �ϴ�
		pService->register_service_route("/file/{id}/block", Http_Operator_Post, RouteCallBackSet::upload_block);

		// ����
		pService->register_service_route("/file/{id}/block", Http_Operator_Get, RouteCallBackSet::download_block);

		return instantiate_plugin_template(pService);
	}
	else
		return NULL;
}