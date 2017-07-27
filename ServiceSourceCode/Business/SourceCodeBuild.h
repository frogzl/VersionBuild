#pragma once
#include "ServiceData.h"

class SourceCodeBuild
{
public:
	SourceCodeBuild(ServiceData *pB);
	~SourceCodeBuild();
	void process_task();
private:

	bool check_inputdata(std::string &sFailedDetail);
	void* get_buildrule_host(std::string sDeployid);
	ServiceData *m_pD;
};
