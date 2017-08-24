#pragma once
#include "ServiceData.h"

class BuildSourceCode
{
public:
	enum ENState
	{
		enBuild,
		enAutoBuild
	};
public:
	BuildSourceCode(ServiceData *pB);
	~BuildSourceCode();
	void process_task(ENState enState);
private:
	bool check_inputdata();
	bool lock_source_code();
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
};
