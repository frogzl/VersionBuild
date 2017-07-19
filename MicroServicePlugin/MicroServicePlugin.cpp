#include "include/MicroServicePlugin.h"
#include "ServiceTemplate.h"
#include "BusinessTemplate.h"
DlLL_API const char* library_version()
{
	return "1";
}

DlLL_API BusinessInterface* create_business()
{
	return new BusinessTemplate();
}

DlLL_API ServiceInterface* create_plugin_template()
{
	return new ServiceTemplate();
}

DlLL_API ServiceInterface*  instantiate_plugin_template(ServiceInterface *pInterface)
{
	ServiceTemplate *pTemp = dynamic_cast<ServiceTemplate*>(pInterface);
	if (pTemp)
		pTemp->change_to_fast_mode();
	return pTemp;
}