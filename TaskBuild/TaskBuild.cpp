// TaskBuild.cpp : 定义 DLL 应用程序的导出函数。
//

#include "MicroTaskPlugin.h"
#include "RouteCallBackSet.h"
// 这是导出函数的一个示例。
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