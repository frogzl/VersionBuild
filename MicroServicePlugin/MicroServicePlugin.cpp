#include "MicroServicePlugin.h"
#include "ServiceTemplate.h"
ServiceInterface* create_plugin_template()
{
	return new ServiceTemplate();
}

ServiceInterface*  instantiate_plugin_template(ServiceInterface *pInterface)
{
	ServiceTemplate *pTemp = dynamic_cast<ServiceTemplate*>(pInterface);
	if (pTemp)
		pTemp->change_to_fast_mode();
	return pTemp;
}