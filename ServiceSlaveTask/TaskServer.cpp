#include "TaskServer.h"


TaskServer::TaskServer()
{
}


TaskServer::~TaskServer()
{
}

void TaskServer::start()
{
	m_hThreadProcessing = (HANDLE)_beginthread(processing_dispatch_callback, 0, this);
	m_hThreadSummary = (HANDLE)_beginthread(summary_dispatch_ccallback, 0, this);
}

void TaskServer::stop()
{

}

void TaskServer::processing_dispatch_callback(void *arg)
{
}

void TaskServer::summary_dispatch_ccallback(void *arg)
{
}

void TaskServer::wait_for_end()
{
	WaitForSingleObject(m_hThreadProcessing, INFINITE);
	WaitForSingleObject(m_hThreadSummary, INFINITE);
}