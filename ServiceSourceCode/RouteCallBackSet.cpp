#include "RouteCallBackSet.h"
#include "Business\SourceCodeBuild.h"
#include "Business\SourceCodeCreate.h"
#include "Business\SourceCodeDelete.h"
#include "Business\SourceCodeDeploy.h"
#include "Business\SourceCodeModify.h"
#include "Business\SourceCodeQuery.h"

void RouteCallBackSet::sourcecode_query(ServiceData *pD)
{
	SourceCodeQuery scq(pD);
	scq.process_task();
}

void RouteCallBackSet::sourcecode_create(ServiceData *pD)
{
	SourceCodeCreate scc(pD);
	scc.process_task();
}

void RouteCallBackSet::sourcecode_modify(ServiceData *pD)
{
	SourceCodeModify scm(pD);
	scm.process_task();
}

void RouteCallBackSet::sourcecode_deploy(ServiceData *pD)
{
	SourceCodeDeploy scd(pD);
	scd.process_task();
}

void RouteCallBackSet::sourcecode_build(ServiceData *pD)
{
	SourceCodeBuild scb(pD);
	scb.process_task();
}

void RouteCallBackSet::sourcecode_delete(ServiceData *pD)
{
	SourceCodeDelete scd(pD);
	scd.process_task();
}
