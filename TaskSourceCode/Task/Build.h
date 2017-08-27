#pragma once
#include "TaskData.h"
class Build
{
public:
	Build(TaskData *pTD);
	~Build();
	void process_task();
private:
	void run_command(string sCmd, string sWorkPath);
	void send_back_result(string sCode, string sMsg);
	void send_back_result(string sCode, string sMsg, Json::Value jValue);
	ULONGLONG  get_dir_free_size(string sDirName);
private:
	TaskData *m_pTD;

};

