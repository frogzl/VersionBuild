#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	static void create_task(ServiceData *pD);
	static void query_task(ServiceData *pD);
	static void delete_task(ServiceData *pD);
	static void finish_task(ServiceData *pD);
};

