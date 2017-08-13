#include "Helper.h"
#include <algorithm>
Helper::Helper()
{
}

Helper::~Helper()
{
}

void Helper::http_request_done(struct evhttp_request *req, void *arg)
{
	printf("send m_request ok...\n");
	Item*pItem = (Item*)arg;
	if (req == NULL)
	{
		pItem->pHttp->set_http_code(0);
		return;
	}
	pItem->pHttp->set_http_code(evhttp_request_get_response_code(req));
	size_t len = evbuffer_get_length(evhttp_request_get_input_buffer(req));
	unsigned char * str = evbuffer_pullup(evhttp_request_get_input_buffer(req), len);
	if (str == NULL)
	{
		printf("len = %d, str == NULL\n", len);
	}
	else
	{
		char *szBuf = new char[len + 1];
		memset(szBuf, 0, len + 1);
		memcpy(szBuf, str, len);
		Json::Value m_inputData;
		Json::Reader reader;
		if (reader.parse(szBuf, m_inputData))
			pItem->pHttp->set_http_respond_data(m_inputData);
		printf("len = %d, str = %s\n", len, szBuf);
		delete[] szBuf;
	}

	event_base_loopbreak((struct event_base*)pItem->pBase);
}