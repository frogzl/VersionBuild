#include "RouteCallBackSet.h"
#include "Business\StartTask.h"

void RouteCallBackSet::process_task(ServiceData *pD)
{
	StartTask st(pD);
	st.process_task();
}