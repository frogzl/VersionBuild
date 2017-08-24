#pragma once
#include "ServiceData.h"

class UpdateBuildRuleResult
{
public:
	UpdateBuildRuleResult(ServiceData *pD);
	~UpdateBuildRuleResult();
	void process_task();
private:
	bool check_inputdata();
protected:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
	std::string _sBuildRuleID;
	std::string _sBuildResultID;
};