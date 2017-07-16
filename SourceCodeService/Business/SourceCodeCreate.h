#pragma once
#include "../Business.h"
#include "../Database/Resource_SourceCode.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Deploy.h"
#include "../Database/BuildRule_Depend.h"
class SourceCodeCreate : public Business
{
public:
	SourceCodeCreate();
	~SourceCodeCreate();

	void process_task();
	void background_process();
};
