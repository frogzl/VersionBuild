#include "RouteCallBackSet.h"
#include "Business\SourceCodeBuild.h"
#include "Business\SourceCodeCreate.h"
#include "Business\SourceCodeDelete.h"
#include "Business\SourceCodeDeploy.h"
#include "Business\SourceCodeModify.h"
#include "Business\SourceCodeQuery.h"

void RouteCallBackSet::sourcecode_query(BusinessInterface *pB)
{
	SourceCodeQuery scq(pB);
	scq.process_task();
}

void RouteCallBackSet::sourcecode_create(BusinessInterface *pB)
{
	SourceCodeCreate scc(pB);
	scc.process_task();
}

void RouteCallBackSet::sourcecode_modify(BusinessInterface *pB)
{
	SourceCodeModify scm(pB);
	scm.process_task();
}

void RouteCallBackSet::sourcecode_deploy(BusinessInterface *pB)
{
	SourceCodeDeploy scd(pB);
	scd.process_task();
}

void RouteCallBackSet::sourcecode_build(BusinessInterface *pB)
{
	SourceCodeBuild scb(pB);
	scb.process_task();
}

void RouteCallBackSet::sourcecode_delete(BusinessInterface *pB)
{
	SourceCodeDelete scd(pB);
	scd.process_task();
}
