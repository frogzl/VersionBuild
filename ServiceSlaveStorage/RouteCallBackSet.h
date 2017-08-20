#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	// 添加主机
	static void upload_block(ServiceData *pD);

	// 查询主机
	static void download_block(ServiceData *pD);
};

