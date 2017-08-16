#pragma once
#include "ServiceData.h"
#include "Helper.h"
using namespace Helper;

class CreateTask
{
public:
	CreateTask(ServiceData *pB);
	~CreateTask();
	void process_task();
private:
	bool check_input_data();
	static bool process_task_callback(Network::Respond_Data *pData, void*);
private:
	ServiceData *m_pD;

	string _sTaskPath;
	// 获取插件唯一标识
	string _sUniqueID;
	// 获取插件版本
	string _sVersion;

};
