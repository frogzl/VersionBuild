#pragma once
#include "ServiceData.h"

class DeleteExecutableRoleDeploymentInformation
{
public:
	DeleteExecutableRoleDeploymentInformation(ServiceData *pB);
	~DeleteExecutableRoleDeploymentInformation();
	void process_task();
private:
	ServiceData *m_pD;
};

