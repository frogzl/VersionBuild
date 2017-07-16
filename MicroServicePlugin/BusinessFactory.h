#pragma once
#include "Business.h"
class BusinessFactory
{
public:
	BusinessFactory();
	~BusinessFactory();
	bool init_business_count(int nCount);
	Business* get_business(const char *szBusinessName);
};

