#pragma once
#include "BusinessInterface.h"
class RouteCallBackSet
{
public:
	static void sourcecode_query(BusinessInterface *pB);
	static void sourcecode_create(BusinessInterface *pB);
	static void sourcecode_modify(BusinessInterface *pB);
	static void sourcecode_deploy(BusinessInterface *pB);
	static void sourcecode_build(BusinessInterface *pB);
	static void sourcecode_delete(BusinessInterface *pB);
};

