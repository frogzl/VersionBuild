#pragma once
#include "ServiceData.h"
class SourceCodeDelete
{
public:
	SourceCodeDelete(ServiceData *pD);
	~SourceCodeDelete();
	void process_task();
protected:
	ServiceData *m_pD;
};
