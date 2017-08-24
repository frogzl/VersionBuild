#include "RouteCallBackSet.h"
#include "Business\Upload.h"
#include "Business\Download.h"

using namespace std;

void RouteCallBackSet::query_file_info(ServiceData *pD)
{
	Upload u(pD);
	u.process_task();
}

void RouteCallBackSet::upload(ServiceData *pD)
{
	Upload u(pD);
	u.process_task();
}

void RouteCallBackSet::download(ServiceData *pD)
{
	Download d(pD);
	d.process_task();
}