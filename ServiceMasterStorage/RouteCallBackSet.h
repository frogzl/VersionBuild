#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	// 添加主机
	static void upload(ServiceData *pD);

	// 查询主机
	static void download(ServiceData *pD);
};

