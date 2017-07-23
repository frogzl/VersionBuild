#include "include/MicroServicePlugin.h"
#include "ServiceTemplate.h"
#include "BusinessTemplate.h"

DLL_API BusinessInterface* create_business()
{
	return new BusinessTemplate();
}

DLL_API ServiceInterface* create_plugin_template()
{
	return new ServiceTemplate();
}

DLL_API ServiceInterface*  instantiate_plugin_template(ServiceInterface *pInterface)
{
	ServiceTemplate *pTemp = dynamic_cast<ServiceTemplate*>(pInterface);
	if (pTemp)
		pTemp->change_to_fast_mode();
	return pTemp;
}