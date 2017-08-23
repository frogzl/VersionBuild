#include "RouteCallBackSet.h"
#include "Business\CreateCompilingToolInstance.h"
#include "Business\CreateCompilingToolTemplate.h"
#include "Business\QueryCompilingToolInstance.h"
#include "Business\QueryCompilingToolTemplate.h"

using namespace std;
// 添加编译工具模板
void RouteCallBackSet::create_compiling_tool_template(ServiceData *pD)
{
	CreateCompilingToolTemplate cctt(pD);
	cctt.process_task();
}

// 查询编译工具模板
void RouteCallBackSet::query_compiling_tool_template(ServiceData *pD)
{
	QueryCompilingToolTemplate qctt(pD);
	qctt.process_task();
}

// 添加编译工具实例
void RouteCallBackSet::create_compiling_tool_instance(ServiceData *pD)
{
	CreateCompilingToolInstance ccti(pD);
	ccti.process_task();
}

// 查询编译工具实例
void RouteCallBackSet::query_compiling_tool_instance(ServiceData *pD)
{
	QueryCompilingToolInstance qcti(pD);
	qcti.process_task();
}