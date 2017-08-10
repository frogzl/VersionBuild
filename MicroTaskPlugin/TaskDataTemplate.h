#pragma once
#include "include/TaskData.h"
using namespace std;
class TaskDataTemplate :public TaskData
{
public:
	TaskDataTemplate();
	~TaskDataTemplate();

	const char* task_id();
	int status();
	Json::Value& data();
	Json::Value& processed_data();
	const char* finish_url();

	void set_task_id(const char* id);
	void set_status(int nStatus);
	void set_successful_result(Json::Value &jResult);
	void set_failure_result(Json::Value &jResult);
private:
	const char *_taskID;
	int _status;
	Json::Value _jData;
	Json::Value _jProcessedData;
	string _sFinishUrl;
};