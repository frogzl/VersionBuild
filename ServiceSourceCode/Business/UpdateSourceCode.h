#pragma once
#include "ServiceData.h"

class UpdateSourceCode
{
public:
	UpdateSourceCode(ServiceData *pB);
	~UpdateSourceCode();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
};
