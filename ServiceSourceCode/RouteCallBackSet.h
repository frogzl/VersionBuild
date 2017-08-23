#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	static void sourcecode_query(ServiceData *pD);
	static void add_source_code(ServiceData *pD);
	static void add_build_rule(ServiceData *pD);
	static void add_build_rule_depends(ServiceData *pD);
	static void add_build_rule_result(ServiceData *pD);
	static void query_source_code(ServiceData *pD);
	static void query_build_rule(ServiceData *pD);
	static void query_build_rule_depends(ServiceData *pD);
	static void query_build_rule_result(ServiceData *pD);
};

