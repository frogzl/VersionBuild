// TaskBuild.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "MicroTaskPlugin.h"
#include "RouteCallBackSet.h"
// ���ǵ���������һ��ʾ����
TaskInterface* produce_one()
{
	TaskInterface* pTask = create_plugin_template();
	pTask->register_task_name("SourceCode");
	pTask->register_task_unique_id("7d11f0f8-ab96-4532-b5a7-4b8d9191e436");
	pTask->register_task_version("1");
	pTask->register_task_route("/sourcecode/build", RouteCallBackSet::sourcecode_build);
	pTask->register_task_route("/sourcecode/deploy", RouteCallBackSet::sourcecode_deploy);
	return instantiate_plugin_template(pTask);
}