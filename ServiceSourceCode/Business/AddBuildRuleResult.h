#pragma once
#include "ServiceData.h"

class AddBuildRuleResult
{
public:
	AddBuildRuleResult(ServiceData *pD);
	~AddBuildRuleResult();
	void process_task();
private:
	bool check_inputdata();
protected:
	ServiceData *m_pD;
};