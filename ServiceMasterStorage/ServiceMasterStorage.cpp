// ServiceMasterStorage.cpp : 定义 DLL 应用程序的导出函数。
//
#include "MicroServicePlugin.h"
#include "RouteCallBackSet.h"
#include "Helper.h"
ServiceInterface* produce_one()
{
	static bool bFirst = true;
	if (bFirst)
	{
		bFirst = false;
		Helper::init_environment();
		ServiceInterface* pService = create_plugin_template();
		pService->register_service_name("MasterStorage");
		pService->register_service_unique_id("f1f1420f-f69d-44cc-a454-313d05f81959");
		pService->register_service_version("1");

		// 上传
		pService->register_service_route("/file", Http_Operator_Post, RouteCallBackSet::upload);

		// 下载
		pService->register_service_route("/file/{id}", Http_Operator_Get, RouteCallBackSet::download);

		return instantiate_plugin_template(pService);
	}
	else
		return NULL;
}