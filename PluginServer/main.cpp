// main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Common.h"
#include "HttpServer.h"
#include "SystemConfig.h"
#include "PluginCenter.h"
int main()
{
	if (initialize_socket_environment())
		return 1;

	PluginCenter::load_service_plugins();

	// 启动http服务
	HttpServer hs(SystemConfig::instance()->m_nWorker);
	hs.start(SystemConfig::instance()->m_nPort, SystemConfig::instance()->m_nBacklog);

	// 等待结束
	hs.wait_for_end();

	PluginCenter::destory();
	clear_socket_environment();
    return 0;
}

