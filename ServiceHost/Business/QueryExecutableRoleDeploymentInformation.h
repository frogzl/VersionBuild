#pragma once
#include "ServiceData.h"
class QueryExecutableRoleDeploymentInformation
{
public:
	QueryExecutableRoleDeploymentInformation(ServiceData *pB);
	~QueryExecutableRoleDeploymentInformation();
	void process_task();
private:
	ServiceData *m_pD;
};

