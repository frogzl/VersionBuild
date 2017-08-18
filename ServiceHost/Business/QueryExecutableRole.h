#pragma once
#include "ServiceData.h"
class QueryExecutableRole
{
public:
	QueryExecutableRole(ServiceData *pB);
	~QueryExecutableRole();
	void process_task();
private:
	ServiceData *m_pD;
};

