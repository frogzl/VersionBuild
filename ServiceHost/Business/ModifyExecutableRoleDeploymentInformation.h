#pragma once
#include "ServiceData.h"

class ModifyExecutableRoleDeploymentInformation
{
public:
	ModifyExecutableRoleDeploymentInformation(ServiceData *pB);
	~ModifyExecutableRoleDeploymentInformation();
	void process_task();
private:
	ServiceData *m_pD;
};

