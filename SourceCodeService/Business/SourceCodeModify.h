#pragma once
#include "Business.h"
class SourceCodeModify : public Business
{
	BUSINESS_OBJECT(SourceCodeModify)
public:
	SourceCodeModify();
	~SourceCodeModify();
protected:
	void process_task();
};