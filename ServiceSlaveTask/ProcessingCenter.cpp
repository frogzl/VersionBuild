#include "ProcessingCenter.h"
#include "Helper.h"

using namespace Helper;
ProcessingCenter::ProcessingCenter()
{
}


ProcessingCenter::~ProcessingCenter()
{
}

bool ProcessingCenter::add_processing_item(Task *pTask)
{
	HANDLE hThread = (HANDLE)_beginthread(process, 0, pTask);
	if (hThread)
		return true;
	else
		return false;
}

void ProcessingCenter::process(void *pParam)
{
	Task *pTask = (Task*)pParam;
	pTask->process();

	Network::Request_Data rd;
	rd.sData = Json::FastWriter().write(pTask->data()->processed_data());
	Network::post2(Network::enReverseProxy, pTask->data()->finish_url(), rd, NULL, NULL);
}