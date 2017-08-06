// main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Common.h"
#include "HttpServer.h"
#include "TaskServer.h"
#include "SystemConfig.h"
#include "PluginCenter.h"
int main()
{
	if (initialize_socket_environment())
		return 1;

	PluginCenter::load_service_plugins();
	PluginCenter::load_task_plugins();

	// 启动Task服务
	TaskServer ts;
	ts.start();

	// 启动http服务
	HttpServer hs(SystemConfig::instance()->m_nWorker);
	hs.start(SystemConfig::instance()->m_nNetworkPort, SystemConfig::instance()->m_nBacklog);

	// 等待结束
	hs.wait_for_end();
	ts.wait_for_end();

	clear_socket_environment();

    return 0;
}

