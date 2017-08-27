#pragma once
#include "TaskData.h"
class Deploy
{
public:
	Deploy(TaskData *pTD);
	~Deploy();
	void process_task();
private:
	ULONGLONG get_dir_free_size(string sDirName);
	void run_command(string sCmd, string sWorkPath);
	void send_back_result(string sCode, string sMsg);
	void send_back_result(string sCode, string sMsg, Json::Value jValue);
private:
	TaskData *m_pTD;
};

