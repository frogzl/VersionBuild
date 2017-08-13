#include "TaskDataTemplate.h"

TaskDataTemplate::TaskDataTemplate()
{
}

TaskDataTemplate::~TaskDataTemplate()
{
}

const char* TaskDataTemplate::task_id()
{
	return _taskID;
}

int TaskDataTemplate::status()
{
	return _status;
}

Json::Value& TaskDataTemplate::data()
{
	return _jData;
}

Json::Value& TaskDataTemplate::processed_data()
{
	return _jProcessedData;
}

const char* TaskDataTemplate::finish_url()
{
	return _sFinishUrl.c_str();
}

void TaskDataTemplate::set_task_id(const char* id)
{
	_taskID = id;
}

void TaskDataTemplate::set_status(int nStatus)
{
	_status = nStatus;
}

void TaskDataTemplate::set_successful_result(Json::Value &jResult)
{
	_status = 0;
	_jProcessedData = jResult;
}

void TaskDataTemplate::set_failure_result(Json::Value &jResult)
{
	_status = 0x8000;
	_jProcessedData = jResult;
}