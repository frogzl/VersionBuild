#pragma once
#include "Business.h"
class SourceCodeDelete : public Business
{
	BUSINESS_OBJECT(SourceCodeDelete)
public:
	SourceCodeDelete();
	~SourceCodeDelete();
protected:
	void process_task();
};
