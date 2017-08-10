#pragma once
#include "ServiceData.h"
class DeleteTask
{
public:
	DeleteTask(ServiceData *pD);
	~DeleteTask();
	void process_task();
protected:
	ServiceData *m_pD;
};
