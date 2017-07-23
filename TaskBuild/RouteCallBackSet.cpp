#include "RouteCallBackSet.h"
#include "Task/Build.h"
#include "Task/Deploy.h"

void RouteCallBackSet::sourcecode_build(TaskData *pTD)
{
	Build b(pTD);
	b.process_task();
}

void RouteCallBackSet::sourcecode_deploy(TaskData *pTD)
{
	Deploy d(pTD);
	d.process_task();
}