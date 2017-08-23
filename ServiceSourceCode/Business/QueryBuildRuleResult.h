#pragma once
#include "ServiceData.h"
class QueryBuildRuleResult
{
public:
	QueryBuildRuleResult(ServiceData *pD);
	~QueryBuildRuleResult();
	void process_task();
protected:
	ServiceData *m_pD;
};