// MicroTaskPlugin.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "include/MicroTaskPlugin.h"

DlLL_API const char* library_version()
{
	return "1";
}

DlLL_API TaskInterface* create_plugin_template()
{
	return new TaskTemplate();
}

DlLL_API TaskInterface*  instantiate_plugin_template(TaskInterface *pInterface)
{
	TaskTemplate *pTemp = dynamic_cast<TaskTemplate*>(pInterface);
	if (pTemp)
		pTemp->change_to_fast_mode();
	return pTemp;
}