#pragma once
#include "Business.h"
class BusinessFactoryTpl
{
public:
	BusinessFactoryTpl();
	~BusinessFactoryTpl();
	
	virtual Business* get_business(const char *szBusinessName) = 0;
};

