#pragma once
#include "ServiceData.h"

class CreateExecutableRoleDeploymentInformation
{
public:
	CreateExecutableRoleDeploymentInformation(ServiceData *pB);
	~CreateExecutableRoleDeploymentInformation();
	void process_task();
private:
	bool check_input_data();
private:
	ServiceData *m_pD;

	string _sExecutableRoleID;
	string _sHostID;
	int _nPort;
};