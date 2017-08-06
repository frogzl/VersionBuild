#include "Service.h"

Service::Service()
{
}

Service::~Service()
{
}

bool Service::process()
{
	return pPlugin->dispatch(nCreateIndex, pData);
}

ServiceData* Service::data()
{
	return pData;
}