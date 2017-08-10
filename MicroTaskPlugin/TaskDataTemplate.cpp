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

string TaskDataTemplate::finish_url()
{
	return _sFinishUrl;
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