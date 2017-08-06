// main.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// ����Task����
	TaskServer ts;
	ts.start();

	// ����http����
	HttpServer hs(SystemConfig::instance()->m_nWorker);
	hs.start(SystemConfig::instance()->m_nNetworkPort, SystemConfig::instance()->m_nBacklog);

	// �ȴ�����
	hs.wait_for_end();
	ts.wait_for_end();

	clear_socket_environment();

    return 0;
}

