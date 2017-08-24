#pragma once
#include "ServiceData.h"

class UpdateBuildRule
{
public:
	UpdateBuildRule(ServiceData *pD);
	~UpdateBuildRule();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
	std::string _sBuildRuleID;
};
