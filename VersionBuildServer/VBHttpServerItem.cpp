#include "VBHttpServerItem.h"
#include "VBRoute.h"

VBHttpServerItem::VBHttpServerItem()
{
	m_enState = enStop;
}


VBHttpServerItem::~VBHttpServerItem()
{
}

void VBHttpServerItem::start(SOCKET s)
{
	m_ebBase = event_base_new();
	if (m_ebBase == NULL)
		return;

	m_eHttp = evhttp_new(m_ebBase);
	if (m_eHttp == NULL)
		return;

	int nRet = evhttp_accept_socket(m_eHttp, s);
	if (nRet != 0)
		return;

	m_enState = enStart;
	evhttp_set_gencb(m_eHttp, generic_callback, this);
	m_hThread = (HANDLE)_beginthread(dispatch, 0, m_ebBase);
}

void VBHttpServerItem::stop()
{
	m_enState = enStop;
	WaitForSingleObject(m_hThread, INFINITE);
}

VBHttpServerItem::ENState VBHttpServerItem::state()
{
	return m_enState;
}

HANDLE VBHttpServerItem::thread_handle()
{
	return m_hThread;
}

void VBHttpServerItem::generic_callback(struct evhttp_request *req, void *arg) 
{
	VBHttpServerItem *pItem = (VBHttpServerItem*)arg;
	if (pItem->state() == enStop)
		return;

	VBRoute::dispatch(req);

	if (pItem->state() == enStop)
		event_base_loopbreak((struct event_base*)arg);
}

void VBHttpServerItem::dispatch(void *arg)
{
	event_base_dispatch((struct event_base*)arg);
}