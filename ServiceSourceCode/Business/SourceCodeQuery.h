#pragma once
#include "BusinessInterface.h"

class SourceCodeQuery
{
public:
	SourceCodeQuery(BusinessInterface *pB);
	~SourceCodeQuery();
	void process_task();
protected:
	BusinessInterface *m_pB;
};
