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

	std::string _sExecutableRoleID;
	std::string _sHostID;
	int _nPort;
};