#pragma once
#include "TaskData.h"
class Build
{
public:
	Build(TaskData *pTD);
	~Build();
	void process_task();
private:
	TaskData *m_pTD;

};

