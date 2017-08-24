#pragma once
#include "ServiceData.h"

class QueryBuildRule
{
public:
	QueryBuildRule(ServiceData *pD);
	~QueryBuildRule();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
	std::string _sBuildRuleID;
};
