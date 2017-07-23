#pragma once
#include "BusinessInterface.h"

class SourceCodeBuild
{
public:
	SourceCodeBuild(BusinessInterface *pB);
	~SourceCodeBuild();
	void process_task();
private:

	bool check_inputdata(std::string &sFailedDetail);
	void* get_buildrule_host(std::string sDeployid);
	BusinessInterface *m_pB;
};
