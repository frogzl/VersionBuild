#include "VBHttpServerItem.h"
#include "VBRoute.h"

VBHttpServerItem::VBHttpServerItem()
{
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

	evhttp_set_gencb(m_eHttp, generic_callback, NULL);
	m_hThread = (HANDLE)_beginthread(dispatch, 0, m_ebBase);
}

void VBHttpServerItem::stop()
{

}

HANDLE VBHttpServerItem::thread_handle()
{
	return m_hThread;
}

void VBHttpServerItem::generic_callback(struct evhttp_request *req, void *arg) 
{
	VBRoute::dispatch(req);
}

void VBHttpServerItem::dispatch(void *arg)
{
	event_base_dispatch((struct event_base*)arg);
}