#pragma once
#include "ServiceData.h"

class QueryBuildRule
{
public:
	QueryBuildRule(ServiceData *pD);
	~QueryBuildRule();
	void process_task();
protected:
	ServiceData *m_pD;
};
