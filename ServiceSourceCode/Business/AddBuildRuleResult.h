#pragma once
#include "ServiceData.h"

class AddBuildRuleResult
{
public:
	AddBuildRuleResult(ServiceData *pD);
	~AddBuildRuleResult();
	void process_task();
protected:
	ServiceData *m_pD;
};