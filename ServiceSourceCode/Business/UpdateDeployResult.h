#pragma once
#include "ServiceData.h"

class UpdateDeployResult
{
public:
	UpdateDeployResult(ServiceData *pB);
	~UpdateDeployResult();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
};
