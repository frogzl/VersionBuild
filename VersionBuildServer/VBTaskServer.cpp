#include "VBTaskServer.h"


VBTaskServer::VBTaskServer()
{
}


VBTaskServer::~VBTaskServer()
{
}

void VBTaskServer::start()
{
	m_hThreadProcessing = (HANDLE)_beginthread(processing_dispatch_callback, 0, this);
	m_hThreadSummary = (HANDLE)_beginthread(summary_dispatch_ccallback, 0, this);
}

void VBTaskServer::stop()
{

}

void VBTaskServer::processing_dispatch_callback(void *arg)
{
}

void VBTaskServer::summary_dispatch_ccallback(void *arg)
{
}

void VBTaskServer::wait_for_end()
{
	WaitForSingleObject(m_hThreadProcessing, INFINITE);
	WaitForSingleObject(m_hThreadSummary, INFINITE);
}