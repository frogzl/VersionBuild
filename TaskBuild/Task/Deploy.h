#pragma once
#include "TaskData.h"
class Deploy
{
public:
	Deploy(TaskData *pTD);
	~Deploy();
	void process_task();
private:
	TaskData *m_pTD;
};

