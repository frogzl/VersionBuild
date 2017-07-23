#pragma once
#include "BusinessInterface.h"
#include "../Database/Resource_SourceCode.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Deploy.h"
#include "../Database/BuildRule_Depend.h"
class SourceCodeCreate
{
public:
	SourceCodeCreate(BusinessInterface *pB);
	~SourceCodeCreate();
	void process_task();
protected:
	BusinessInterface *m_pB;
};
