#pragma once
#include "ServiceData.h"

class QueryCompilingToolTemplate
{
public:
	QueryCompilingToolTemplate(ServiceData *pB);
	~QueryCompilingToolTemplate();
	void process_task();
private:
	ServiceData *m_pD;
};
