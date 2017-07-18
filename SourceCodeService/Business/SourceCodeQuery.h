#pragma once
#include "Business.h"

class SourceCodeQuery : public Business
{
	BUSINESS_OBJECT(SourceCodeQuery)
public:
	SourceCodeQuery();
	~SourceCodeQuery();
protected:
	void process_task();
};
