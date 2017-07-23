#pragma once
#include "BusinessInterface.h"
class SourceCodeModify
{
public:
	SourceCodeModify(BusinessInterface *pB);
	~SourceCodeModify();
	void process_task();
protected:
	BusinessInterface *m_pB;
};