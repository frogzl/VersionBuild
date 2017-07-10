#pragma once
#include "Common.h"

class VBHttpServerItem
{

public:
	VBHttpServerItem();
	~VBHttpServerItem();
public:
	void start(SOCKET s);
	void stop();

	HANDLE thread_handle();
private:
	static void generic_callback(struct evhttp_request *req, void *arg);
	static void dispatch(void *arg);
private:
	struct event_base *m_ebBase;
	struct evhttp *m_eHttp;
	HANDLE m_hThread;
};

