#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	// ��ӱ��빤��ģ��
	static void create_compiling_tool_template(ServiceData *pD);

	// ��ѯ���빤��ģ��
	static void query_compiling_tool_template(ServiceData *pD);

	// ��ӱ��빤��ʵ��
	static void create_compiling_tool_instance(ServiceData *pD);

	// ��ѯ���빤��ʵ��
	static void query_compiling_tool_instance(ServiceData *pD);
};

