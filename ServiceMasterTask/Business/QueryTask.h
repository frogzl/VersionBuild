#pragma once
#include "ServiceData.h"

class QueryTask
{
public:
	QueryTask(ServiceData *pD);
	~QueryTask();
	void process_task();
protected:
	ServiceData *m_pD;
};
