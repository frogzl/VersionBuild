#pragma once
#include "Business.h"

class SourceCodeDeploy : public Business
{
	BUSINESS_OBJECT(SourceCodeDeploy)
public:
	SourceCodeDeploy();
	~SourceCodeDeploy();
protected:
	void process_task();
};