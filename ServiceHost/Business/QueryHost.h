#pragma once
#include "ServiceData.h"

class QueryHost
{
public:
	QueryHost(ServiceData *pD);
	~QueryHost();
	void process_task();
private:
	ServiceData *m_pD;
};
