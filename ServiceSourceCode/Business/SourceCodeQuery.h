#pragma once
#include "ServiceData.h"

class SourceCodeQuery
{
public:
	SourceCodeQuery(ServiceData *pD);
	~SourceCodeQuery();
	void process_task();
protected:
	ServiceData *m_pD;
};
