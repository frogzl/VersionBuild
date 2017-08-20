#include "RouteCallBackSet.h"
#include "Business\UploadBlock.h"
#include "Business\DownloadBlock.h"

using namespace std;
void RouteCallBackSet::upload_block(ServiceData *pD)
{
	UploadBlock ub(pD);
	ub.process_task();
}

void RouteCallBackSet::download_block(ServiceData *pD)
{
	DownloadBlock db(pD);
	db.process_task();
}