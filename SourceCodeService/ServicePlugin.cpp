#include "stdafx.h"
#include "ServicePlugin.h"

bool ServicePlugin::init_route_count(int nCount)
{
	return ServiceTemplate::init_route_count(nCount);
}

bool ServicePlugin::register_http_get(const char *szPath, const char *szBusinessName)
{
	return ServiceTemplate::register_http_get(szPath, szBusinessName);
}

bool ServicePlugin::register_http_post(const char *szPath, const char *szBusinessName)
{
	return ServiceTemplate::register_http_post(szPath, szBusinessName);
}

bool ServicePlugin::register_http_head(const char *szPath, const char *szBusinessName)
{
	return ServiceTemplate::register_http_head(szPath, szBusinessName);
}

bool ServicePlugin::register_http_put(const char *szPath, const char *szBusinessName)
{
	return ServiceTemplate::register_http_put(szPath, szBusinessName);
}

bool ServicePlugin::register_http_delete(const char *szPath, const char *szBusinessName)
{
	return ServiceTemplate::register_http_delete(szPath, szBusinessName);
}

bool ServicePlugin::register_http_trace(const char *szPath, const char *szBusinessName)
{
	return ServiceTemplate::register_http_trace(szPath, szBusinessName);
}

bool ServicePlugin::register_http_options(const char *szPath, const char *szBusinessName)
{
	return ServiceTemplate::register_http_options(szPath, szBusinessName);
}

bool ServicePlugin::register_service_name(const char *szName)
{
	return ServiceTemplate::register_service_name(szName);
}

bool ServicePlugin::register_service_unique_id(const char *szID)
{
	return ServiceTemplate::register_service_unique_id(szID);
}

bool ServicePlugin::register_service_version(const char *szVersion)
{
	return ServiceTemplate::register_service_version(szVersion);
}

bool ServicePlugin::register_service_business_factory(BusinessFactoryTpl *pFactory)
{
	return ServiceTemplate::register_service_business_factory(pFactory);
}