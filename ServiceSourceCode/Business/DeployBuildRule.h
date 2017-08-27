#pragma once
#include "ServiceData.h"
#include "Helper.h"
using namespace Helper;
class DeployBuildRule
{
public:
	DeployBuildRule(ServiceData *pB);
	~DeployBuildRule();
	void process_task();
private:
	bool check_inputdata();
	bool lock_source_code();
	static bool cb_get_version_control_ins(Network::Respond_Data *pData, void*);
	static bool cb_create_task(Network::Respond_Data *pData, void*);
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
	std::string _sBuildRuleID;
	std::string _sPluginDeployID;
};
