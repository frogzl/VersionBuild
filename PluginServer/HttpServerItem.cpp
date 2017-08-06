#include "HttpServerItem.h"

HttpServerItem::HttpServerItem()
{
	m_enState = enStop;
}

HttpServerItem::~HttpServerItem()
{
}

void HttpServerItem::start(SOCKET s)
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

void HttpServerItem::stop()
{
	m_enState = enStop;
	WaitForSingleObject(m_hThread, INFINITE);
}

HttpServerItem::ENState HttpServerItem::state()
{
	return m_enState;
}

HANDLE HttpServerItem::thread_handle()
{
	return m_hThread;
}

void HttpServerItem::dispatch(void *arg)
{
	event_base_dispatch((struct event_base*)arg);
}

void HttpServerItem::generic_callback(struct evhttp_request *req, void *arg)
{
	HttpServerItem *pItem = (HttpServerItem*)arg;
	if (pItem->state() == enStop)
		return;

	Service *pService = PluginCenter::parse_service_path(request_operator(req).c_str(), request_path(req).c_str());
	if (pService)
	{
		init_header_info(req, pService);
		init_condition_info(req, pService);
		init_body_info(req, pService);
		pService->process();
		respond_client(req, pService);
		PluginCenter::free_service(pService);
	}
	else
		evhttp_send_error(req, HTTP_NOTIMPLEMENTED, "");
	if (pItem->state() == enStop)
		event_base_loopbreak((struct event_base*)arg);
}

string HttpServerItem::request_operator(struct evhttp_request *req)
{
	switch (evhttp_request_get_command(req))
	{
	case EVHTTP_REQ_GET:
		return Http_Operator_Get;
	case EVHTTP_REQ_POST:
		return Http_Operator_Post;
	case EVHTTP_REQ_HEAD:
		return Http_Operator_Head;
	case EVHTTP_REQ_PUT:
		return Http_Operator_Put;
	case EVHTTP_REQ_DELETE:
		return Http_Operator_Delete;
	case EVHTTP_REQ_OPTIONS:
		return Http_Operator_Options;
	case EVHTTP_REQ_TRACE:
		return Http_Operator_Trace;
	case EVHTTP_REQ_CONNECT:
	case EVHTTP_REQ_PATCH:
	default:
		evhttp_send_error(req, HTTP_BADMETHOD, "Your operator type is not supported.");
		return Http_Operator_Other;
	}

}

string HttpServerItem::request_path(struct evhttp_request *req)
{
	const char *uri = evhttp_request_get_uri(req);
	struct evhttp_uri *decoded = evhttp_uri_parse(uri);
	if (!decoded)
	{
		printf("It's not a good URI.\n");
		evhttp_send_error(req, HTTP_BADREQUEST, "It's not a good URI.");
		return "";
	}
	
	string sRet = evhttp_uri_get_path(decoded);
	if (decoded)
		evhttp_uri_free(decoded);
	return sRet;
}

void HttpServerItem::init_header_info(struct evhttp_request *req, Service *pService)
{
	struct evkeyvalq *headers;
	struct evkeyval *header;
	headers = evhttp_request_get_input_headers(req);
	for (header = headers->tqh_first; header; header = header->next.tqe_next)
		pService->data()->insert_request_header(header->key, header->value);
}

void HttpServerItem::init_condition_info(struct evhttp_request *req, Service *pService)
{
	if (evhttp_request_get_command((const struct evhttp_request *)req) != EVHTTP_REQ_GET)
		return;

	struct evhttp_uri *decoded = evhttp_uri_parse(evhttp_request_get_uri((const struct evhttp_request *)req));
	const char *szQuery = evhttp_uri_get_query(decoded);

	if (szQuery == NULL)
		return;
	else
	{
		string sQuery(szQuery);
		vector<string> vecQuery;
		split(sQuery, "&", &vecQuery);
		for (int nIndex = 0; nIndex < vecQuery.size(); nIndex++)
		{
			vector<string> vecParam;
			split(vecQuery[nIndex], "=", &vecParam);
			if (vecParam.size() == 2)
				pService->data()->insert_request_condition(vecParam[0].c_str(), vecParam[1].c_str());
		}

		if (decoded)
			evhttp_uri_free(decoded);
	}
}

void HttpServerItem::init_body_info(struct evhttp_request *req, Service *pService)
{
	char *szBuf = NULL;
	struct evbuffer *buf = evhttp_request_get_input_buffer(req);
	if (evbuffer_get_length(buf))
	{
		int n;
		szBuf = new char[evbuffer_get_length(buf) + 1];
		n = evbuffer_remove(buf, szBuf, evbuffer_get_length(buf) + 1);
		if (n > 0)
		{
			Json::Reader reader;
			reader.parse(szBuf, pService->data()->request_data().jData);
		}
		if (szBuf)
		{
			delete[] szBuf;
			szBuf = NULL;
		}
	}
}

void HttpServerItem::respond_client(struct evhttp_request *req, Service *pService)
{
	evhttp_add_header(evhttp_request_get_output_headers((struct evhttp_request *)req), "Content-Type", "application/json");
	struct evbuffer *evb = evbuffer_new();
	string sReplyData = Json::FastWriter().write(pService->data()->respond_data().jData);
	sReplyData = sReplyData.substr(0, sReplyData.length() - 1);
	evbuffer_add_printf(evb, "%s", sReplyData.c_str());
	
	map<std::string, std::string>::iterator it = pService->data()->respond_data().mHeaders.begin();
	while (it != pService->data()->respond_data().mHeaders.end())
	{
		evhttp_add_header(evhttp_request_get_output_headers((struct evhttp_request *)req), it->first.c_str(), it->second.c_str());
		it++;
	}
	evhttp_send_reply((struct evhttp_request *)req, pService->data()->respond_data().nHttpStatus, "", evb);
	if (evb)
		evbuffer_free(evb);
}