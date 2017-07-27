#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	static void sourcecode_query(ServiceData *pD);
	static void sourcecode_create(ServiceData *pD);
	static void sourcecode_modify(ServiceData *pD);
	static void sourcecode_deploy(ServiceData *pD);
	static void sourcecode_build(ServiceData *pD);
	static void sourcecode_delete(ServiceData *pD);
};

