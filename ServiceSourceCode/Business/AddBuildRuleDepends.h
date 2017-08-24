#pragma once
#include "ServiceData.h"
class AddBuildRuleDepends
{
public:
	AddBuildRuleDepends(ServiceData *pD);
	~AddBuildRuleDepends();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sBuildRuleID;
	std::string _sDependSourceCodeID;
	std::string _sDependBuildRuleID;
	std::string _sDependBuildResultID;
	std::string _sDependUsageMode;
};
