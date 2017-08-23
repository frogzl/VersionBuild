#include "RouteCallBackSet.h"
#include "Business/AddBuildRule.h"
#include "Business/AddBuildRuleDepends.h"
#include "Business/AddBuildRuleResult.h"
#include "Business/AddSourceCode.h"
#include "Business/QueryBuildRule.h"
#include "Business/QueryBuildRuleDepends.h"
#include "Business/QueryBuildRuleResult.h"
#include "Business/QuerySourceCode.h"

void RouteCallBackSet::add_source_code(ServiceData *pD)
{
	AddSourceCode asc(pD);
	asc.process_task();
}

void RouteCallBackSet::add_build_rule(ServiceData *pD)
{
	AddBuildRule abr(pD);
	abr.process_task();
}

void RouteCallBackSet::add_build_rule_depends(ServiceData *pD)
{
	AddBuildRuleDepends abrd(pD);
	abrd.process_task();
}

void RouteCallBackSet::add_build_rule_result(ServiceData *pD)
{
	AddBuildRuleResult abrr(pD);
	abrr.process_task();
}

void RouteCallBackSet::query_source_code(ServiceData *pD)
{
	QuerySourceCode qsc(pD);
	qsc.process_task();
}

void RouteCallBackSet::query_build_rule(ServiceData *pD)
{
	QueryBuildRule qbr(pD);
	qbr.process_task();
}

void RouteCallBackSet::query_build_rule_depends(ServiceData *pD)
{
	QueryBuildRuleDepends qbrd(pD);
	qbrd.process_task();
}

void RouteCallBackSet::query_build_rule_result(ServiceData *pD)
{
	QueryBuildRuleResult qbrr(pD);
	qbrr.process_task();
}
