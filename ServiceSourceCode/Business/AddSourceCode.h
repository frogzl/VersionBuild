#pragma once
#include "ServiceData.h"

class AddSourceCode
{
public:
	AddSourceCode(ServiceData *pB);
	~AddSourceCode();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sName;
	std::string _sDiscription;
	std::string	 _sVersionControlID;
	int _nStartVersion;
	int _nBuildState;
};
