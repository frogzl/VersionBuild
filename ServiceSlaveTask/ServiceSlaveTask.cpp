// ServiceSlaveTask.cpp : 定义 DLL 应用程序的导出函数。
//

#include "MicroServicePlugin.h"
#include "RouteCallBackSet.h"
#include "PluginCenter.h"
#include "TaskServer.h"
#include "Helper.h"
ServiceInterface* produce_one()
{
	static bool bFirst = true;
	if (bFirst)
	{
		bFirst = false;
		PluginCenter::load_task_plugins();
		Helper::init_environment();

		// 启动Task服务
		static TaskServer ts;
		ts.start();

		ServiceInterface* pService = create_plugin_template();
		pService->register_service_name("SlaveTask");
		pService->register_service_unique_id("cc0e7465-9c6d-4802-8786-2bafd9ef9ff4");
		pService->register_service_version("1");
		pService->register_service_route("/task/{id}/process", Http_Operator_Post, RouteCallBackSet::process_task);
		return instantiate_plugin_template(pService);
	}
	else
		return NULL;
}