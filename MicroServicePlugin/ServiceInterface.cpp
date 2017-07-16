#include "ServiceInterface.h"

ServiceInterface::~ServiceInterface() 
{
}

void ServiceInterface::destory() 
{ 
	delete this; 
}

const char* ServiceInterface::library_version()
{
	return "1.0";
}