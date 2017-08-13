#pragma once
#include <json/json.h>

class TaskData
{
public:

public:
	virtual ~TaskData() {};
	// Ψһ��ʶ
	virtual const char* task_id() = 0;
	// ״̬
	virtual int status() = 0;
	// ����������
	virtual Json::Value& data() = 0;
	// ����������
	virtual Json::Value& processed_data() = 0;
	// ����URL
	virtual const char* finish_url() = 0;

	virtual void set_task_id(const char* id) = 0;
	virtual void set_status(int nStatus) = 0;
	virtual void set_successful_result(Json::Value &jResult) = 0;
	virtual void set_failure_result(Json::Value &jResult) = 0;
};

typedef void(*FuncTaskProcess)(TaskData*);