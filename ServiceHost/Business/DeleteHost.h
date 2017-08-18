#pragma once
#include "ServiceData.h"
class DeleteHost
{
public:
	DeleteHost(ServiceData *pD);
	~DeleteHost();
	void process_task();
protected:
	ServiceData *m_pD;
};
