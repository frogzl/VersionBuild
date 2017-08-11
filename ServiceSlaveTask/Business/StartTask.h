#pragma once
#include "ServiceData.h"

class StartTask
{
public:
	StartTask(ServiceData *pB);
	~StartTask();
	void process_task();
private:
	ServiceData *m_pD;
};
