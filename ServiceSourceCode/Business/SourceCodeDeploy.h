#pragma once
#include "ServiceData.h"

class SourceCodeDeploy
{
public:
	SourceCodeDeploy(ServiceData *pD);
	~SourceCodeDeploy();
	void process_task();
protected:
	ServiceData *m_pD;
};