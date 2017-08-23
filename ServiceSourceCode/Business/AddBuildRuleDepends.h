#pragma once
#include "ServiceData.h"
class AddBuildRuleDepends
{
public:
	AddBuildRuleDepends(ServiceData *pD);
	~AddBuildRuleDepends();
	void process_task();
protected:
	ServiceData *m_pD;
};
