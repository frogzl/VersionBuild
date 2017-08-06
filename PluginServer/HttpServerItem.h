#pragma once
#include "Common.h"
#include "PluginCenter.h"

class HttpServerItem
{
	enum ENState
	{
		enStart,
		enStop
	};
public:
	HttpServerItem();
	~HttpServerItem();
public:
	void start(SOCKET s);
	void stop();
	ENState state();
	HANDLE thread_handle();
private:
	static void dispatch(void *arg);
	static void generic_callback(struct evhttp_request *req, void *arg);
	static string request_operator(struct evhttp_request *req);
	static string request_path(struct evhttp_request *req);
	static void init_header_info(struct evhttp_request *req, Service *pService);
	static void init_condition_info(struct evhttp_request *req, Service *pService);
	static void init_body_info(struct evhttp_request *req, Service *pService);
	static void respond_client(struct evhttp_request *req, Service *pService);
private:
	struct event_base *m_ebBase;
	struct evhttp *m_eHttp;
	HANDLE m_hThread;
	ENState m_enState;
};

