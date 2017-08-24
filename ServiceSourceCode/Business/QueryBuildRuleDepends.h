#pragma once
#include "ServiceData.h"
class QueryBuildRuleDepends
{
public:
	QueryBuildRuleDepends(ServiceData *pD);
	~QueryBuildRuleDepends();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
	std::string _sBuildRuleID;
	std::string _sBuildRuleDependID;
};