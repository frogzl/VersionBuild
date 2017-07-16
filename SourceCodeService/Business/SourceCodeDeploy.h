#pragma once
#include "../Business.h"

class SourceCodeDeploy : public Business
{
public:
	SourceCodeDeploy();
	~SourceCodeDeploy();

	void process_task();
	void background_process();
};