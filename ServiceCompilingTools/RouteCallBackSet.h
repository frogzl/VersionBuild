#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	// 添加编译工具模板
	static void create_compiling_tool_template(ServiceData *pD);

	// 查询编译工具模板
	static void query_compiling_tool_template(ServiceData *pD);

	// 添加编译工具实例
	static void create_compiling_tool_instance(ServiceData *pD);

	// 查询编译工具实例
	static void query_compiling_tool_instance(ServiceData *pD);
};

