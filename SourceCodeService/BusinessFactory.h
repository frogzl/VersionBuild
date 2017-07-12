#pragma once
#include "BusinessFactoryTpl.h"
class BusinessFactory : public BusinessFactoryTpl
{
public:
	BusinessFactory();
	~BusinessFactory();
	
	Business* get_business(const char *szBusinessName);
};

