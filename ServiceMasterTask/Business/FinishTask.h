#pragma once
#include "ServiceData.h"

class FinishTask
{
public:
	FinishTask(ServiceData *pD);
	~FinishTask();
	void process_task();
protected:
	ServiceData *m_pD;
};