#include "RouteCallBackSet.h"
#include "Business\CreateCompilingToolInstance.h"
#include "Business\CreateCompilingToolTemplate.h"
#include "Business\QueryCompilingToolInstance.h"
#include "Business\QueryCompilingToolTemplate.h"

using namespace std;
// ��ӱ��빤��ģ��
void RouteCallBackSet::create_compiling_tool_template(ServiceData *pD)
{
	CreateCompilingToolTemplate cctt(pD);
	cctt.process_task();
}

// ��ѯ���빤��ģ��
void RouteCallBackSet::query_compiling_tool_template(ServiceData *pD)
{
	QueryCompilingToolTemplate qctt(pD);
	qctt.process_task();
}

// ��ӱ��빤��ʵ��
void RouteCallBackSet::create_compiling_tool_instance(ServiceData *pD)
{
	CreateCompilingToolInstance ccti(pD);
	ccti.process_task();
}

// ��ѯ���빤��ʵ��
void RouteCallBackSet::query_compiling_tool_instance(ServiceData *pD)
{
	QueryCompilingToolInstance qcti(pD);
	qcti.process_task();
}