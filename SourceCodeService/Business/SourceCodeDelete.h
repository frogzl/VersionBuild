#pragma once
#include "BusinessInterface.h"
class SourceCodeDelete
{
public:
	SourceCodeDelete(BusinessInterface *pB);
	~SourceCodeDelete();
	void process_task();
protected:
	BusinessInterface *m_pB;
};
