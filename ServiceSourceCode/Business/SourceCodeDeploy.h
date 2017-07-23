#pragma once
#include "BusinessInterface.h"

class SourceCodeDeploy
{
public:
	SourceCodeDeploy(BusinessInterface *pB);
	~SourceCodeDeploy();
	void process_task();
protected:
	BusinessInterface *m_pB;
};