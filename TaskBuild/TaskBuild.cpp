// TaskBuild.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "MicroTaskPlugin.h"
#include "RouteCallBackSet.h"
// ���ǵ���������һ��ʾ����
TaskInterface* produce_one()
{
	TaskInterface* pTask = create_plugin_template();
	pTask->register_task_name("SourceCode");
	pTask->register_task_unique_id("{4d02dad3-175d-4906-a48d-07f55d3bfdaf}");
	pTask->register_task_version("1");
	pTask->register_task_route("/sourcecode/build", RouteCallBackSet::sourcecode_build);
	pTask->register_task_route("/sourcecode/deploy", RouteCallBackSet::sourcecode_deploy);
	return instantiate_plugin_template(pTask);
}