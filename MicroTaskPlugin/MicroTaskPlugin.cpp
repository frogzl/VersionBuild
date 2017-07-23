// MicroTaskPlugin.cpp : 定义 DLL 应用程序的导出函数。
//
#include "include/MicroTaskPlugin.h"
#include "TaskTemplate.h"
#include "TaskDataTemplate.h"

DLL_API TaskData* create_business()
{
	return new TaskDataTemplate();
}

DLL_API TaskInterface* create_plugin_template()
{
	return new TaskTemplate();
}

DLL_API TaskInterface*  instantiate_plugin_template(TaskInterface *pInterface)
{
	TaskTemplate *pTemp = dynamic_cast<TaskTemplate*>(pInterface);
	if (pTemp)
		pTemp->change_to_fast_mode();
	return pTemp;
}