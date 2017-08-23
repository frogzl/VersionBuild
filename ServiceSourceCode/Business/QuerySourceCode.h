#pragma once
#include "ServiceData.h"
class QuerySourceCode
{
public:
	QuerySourceCode(ServiceData *pD);
	~QuerySourceCode();
	void process_task();
protected:
	ServiceData *m_pD;
};