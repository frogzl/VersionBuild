#include "MicroServicePlugin.h"
#include "ServiceTemplate.h"
ServiceInterface* create_plugin()
{
	return new ServiceTemplate();
}