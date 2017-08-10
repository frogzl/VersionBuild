#pragma once
#include "ServiceData.h"
#include "../Database/Resource_SourceCode.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Deploy.h"
#include "../Database/BuildRule_Depend.h"
class QueryTask
{
public:
	QueryTask(ServiceData *pD);
	~QueryTask();
	void process_task();
protected:
	ServiceData *m_pD;
};
