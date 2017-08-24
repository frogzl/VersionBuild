#pragma once
#include "ServiceData.h"
class QuerySourceCode
{
public:
	QuerySourceCode(ServiceData *pD);
	~QuerySourceCode();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
};