#pragma once
#include "ServiceData.h"
class QueryBuildRuleResult
{
public:
	QueryBuildRuleResult(ServiceData *pD);
	~QueryBuildRuleResult();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
	std::string _sBuildRuleID;
	std::string _sBuildResultID;
};