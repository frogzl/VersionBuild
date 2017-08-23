#pragma once
#include "ServiceData.h"
class QueryBuildRuleDepends
{
public:
	QueryBuildRuleDepends(ServiceData *pD);
	~QueryBuildRuleDepends();
	void process_task();
protected:
	ServiceData *m_pD;
};