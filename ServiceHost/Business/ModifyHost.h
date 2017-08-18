#pragma once
#include "ServiceData.h"

class ModifyHost
{
public:
	ModifyHost(ServiceData *pD);
	~ModifyHost();
	void process_task();
protected:
	ServiceData *m_pD;
};