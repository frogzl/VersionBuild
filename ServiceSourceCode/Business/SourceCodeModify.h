#pragma once
#include "ServiceData.h"
class SourceCodeModify
{
public:
	SourceCodeModify(ServiceData *pD);
	~SourceCodeModify();
	void process_task();
protected:
	ServiceData *m_pD;
};