#include "RouteCallBackSet.h"
#include "Business\CreateTask.h"
#include "Business\QueryTask.h"
#include "Business\DeleteTask.h"
#include "Business\FinishTask.h"

void RouteCallBackSet::create_task(ServiceData *pD)
{
	CreateTask ct(pD);
	ct.process_task();
}
void RouteCallBackSet::query_task(ServiceData *pD)
{
	QueryTask qt(pD);
	qt.process_task();
}
void RouteCallBackSet::delete_task(ServiceData *pD)
{
	DeleteTask dt(pD);
	dt.process_task();
}
void RouteCallBackSet::finish_task(ServiceData *pD)
{
	FinishTask ft(pD);
	ft.process_task();
}