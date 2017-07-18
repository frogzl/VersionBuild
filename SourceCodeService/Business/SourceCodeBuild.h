#pragma once
#include "Business.h"

class SourceCodeBuild : public Business
{
	BUSINESS_OBJECT(SourceCodeBuild)
public:
	SourceCodeBuild();
	~SourceCodeBuild();

private:
	void process_task();

	bool check_inputdata(string &sFailedDetail);
	void* get_buildrule_host(string sDeployid);
};
