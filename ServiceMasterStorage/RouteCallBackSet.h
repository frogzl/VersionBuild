#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	// 查询存储信息
	void query_file_info(ServiceData *pD);

	// 添加主机
	static void upload(ServiceData *pD);

	// 查询主机
	static void download(ServiceData *pD);
};

