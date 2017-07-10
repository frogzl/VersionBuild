#include "Controller.h"
#include <string>
#include <vector>
#include "../Exception/HttpRequestException.h"
#include "../Business/Business.h"
using namespace std;
namespace Controller
{
	Controller::Controller(struct evhttp_request  *req)
	{
		m_req = req;
	}


	Controller::~Controller()
	{
	}

	void Controller::do_business(void *pBusiness)
	{
		B::Business *p = (B::Business*)pBusiness;
		if (p == NULL)
			return;
		string sHost;
		int nPort;

		if (!p->is_need_redirect(sHost, nPort))
		{
			p->process_task();
			send_respond(p);
			delete p;
		}
		else
		{
			switch (evhttp_request_get_command((const struct evhttp_request *)m_req))
			{
			case EVHTTP_REQ_GET:
				redirect_request_get(sHost, nPort);
				break;
			case EVHTTP_REQ_POST:
				redirect_request_post(sHost, nPort);
				break;
			}
		}
	}

	bool Controller::get_input_parameters(map<string, string> &mapParameter)
	{
		if (evhttp_request_get_command((const struct evhttp_request *)m_req) != EVHTTP_REQ_GET)
			return false;

		struct evhttp_uri *decoded = evhttp_uri_parse(evhttp_request_get_uri((const struct evhttp_request *)m_req));
		const char *szQuery = evhttp_uri_get_query(decoded);


		if (szQuery == NULL)
			return false;
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
				{
					mapParameter.insert(pair<string, string>(vecParam[0], vecParam[1]));
				}
			}

			if (decoded)
				evhttp_uri_free(decoded);

			if (mapParameter.size() > 0)
				return true;
			else
				return false;
		}
	}

	char* Controller::get_input_buffer()
	{
		char *szBuf = NULL;
		struct evbuffer *buf = evhttp_request_get_input_buffer(m_req);
		puts("Input data: <<<");
		if (evbuffer_get_length(buf))
		{
			int n;
			szBuf = new char[evbuffer_get_length(buf) + 1];
			n = evbuffer_remove(buf, szBuf, evbuffer_get_length(buf) + 1);
			if (n > 0)
				(void) fwrite(szBuf, 1, n, stdout);
			else
			{
				if (szBuf)
				{
					delete[] szBuf;
					szBuf = NULL;
				}
			}
		}
		puts(">>>");
		return szBuf;
	}

	char* Controller::get_input_buffer(struct evhttp_request  *req)
	{
		char *szBuf = NULL;
		struct evbuffer *buf = evhttp_request_get_input_buffer(req);
		puts("Input data: <<<");
		if (evbuffer_get_length(buf))
		{
			int n;
			szBuf = new char[evbuffer_get_length(buf) + 1];
			n = evbuffer_remove(buf, szBuf, evbuffer_get_length(buf) + 1);
			if (n > 0)
				(void) fwrite(szBuf, 1, n, stdout);
			else
			{
				if (szBuf)
				{
					delete[] szBuf;
					szBuf = NULL;
				}
			}
		}
		puts(">>>");
		return szBuf;
	}

	bool Controller::get_input_headers(map<string, string> &mapHeader)
	{
		struct evkeyvalq *headers;
		struct evkeyval *header;
		headers = evhttp_request_get_input_headers(m_req);
		for (header = headers->tqh_first; header; header = header->next.tqe_next)
			mapHeader.insert(pair<string, string>(header->key, header->value));

		if (mapHeader.size() > 0)
			return true;
		else
			return false;
	}

	bool Controller::get_input_headers(struct evhttp_request  *req, map<string, string> &mapHeader)
	{
		struct evkeyvalq *headers;
		struct evkeyval *header;
		headers = evhttp_request_get_input_headers(req);
		for (header = headers->tqh_first; header; header = header->next.tqe_next)
			mapHeader.insert(pair<string, string>(header->key, header->value));

		if (mapHeader.size() > 0)
			return true;
		else
			return false;
	}

	void Controller::send_respond_success(char *szBuf)
	{
		struct evbuffer *evb = evbuffer_new();
		evhttp_add_header(evhttp_request_get_output_headers((struct evhttp_request *)m_req), "Content-Type", "application/json");
		evbuffer_add_printf(evb, "%s", szBuf);
		evhttp_send_reply((struct evhttp_request *)m_req, HTTP_OK, "OK", evb);
		if (evb)
			evbuffer_free(evb);
	}

	void Controller::redirect_request_get(string sHost, int nPort)
	{
		struct event_base* baseRedirect;
		struct evhttp_connection* connRedirect;
		struct evhttp_request* reqRedirect;

		baseRedirect = event_base_new();
		connRedirect = evhttp_connection_base_new(baseRedirect, NULL, sHost.c_str(), nPort);

		reqRedirect = evhttp_request_new(http_request_done, baseRedirect);
		// 初始化头
		map<string, string> mapHeaders;
		get_input_headers(mapHeaders);
		map<string, string>::const_iterator cit = mapHeaders.cbegin();
		while (cit != mapHeaders.cend())
		{
			if (cit->first.compare("Host") != 0)
				evhttp_add_header(evhttp_request_get_output_headers(reqRedirect), cit->first.c_str(), cit->second.c_str());
			cit++;
		}
		evhttp_add_header(evhttp_request_get_output_headers(reqRedirect), "Host", sHost.c_str());

		// 初始化请求路径
		struct evhttp_uri *decoded = evhttp_uri_parse(evhttp_request_get_uri(m_req));
		string sPath = evhttp_uri_get_path(decoded);
		sPath += "?";
		sPath += evhttp_uri_get_query(decoded);

		if (decoded)
			evhttp_uri_free(decoded);

		// 发起请求
		evhttp_make_request(connRedirect, reqRedirect, EVHTTP_REQ_GET, sPath.c_str());
		event_base_dispatch(baseRedirect);

		char *szBuf = get_input_buffer(reqRedirect);
		evhttp_connection_free(connRedirect);
		event_base_free(baseRedirect);

		// 返回数据
		if (szBuf)
		{
			// 获取range头
			map<string, string> mapHeader;
			if (!get_input_headers(reqRedirect, mapHeader))
			{
				delete[] szBuf;
				throw HttpRequestException(HTTP_BADREQUEST, "1", "redirect http don't have header.");
			}

			map<string, string>::iterator itRange = mapHeader.find("Range");
			if (itRange != mapHeader.end())
				evhttp_add_header(evhttp_request_get_output_headers(m_req), "Range", itRange->second.c_str());

			send_respond_success(szBuf);
			delete[] szBuf;
		}
		else
		{
			throw HttpRequestException(HTTP_INTERNAL, "1", "read respond data failed!");
		}
	}

	void Controller::redirect_request_post(string sHost, int nPort)
	{
		struct event_base* baseRedirect;
		struct evhttp_connection* connRedirect;
		struct evhttp_request* reqRedirect;

		baseRedirect = event_base_new();
		connRedirect = evhttp_connection_base_new(baseRedirect, NULL, sHost.c_str(), nPort);

		reqRedirect = evhttp_request_new(http_request_done, baseRedirect);
		// 初始化头
		map<string, string> mapHeaders;
		get_input_headers(mapHeaders);
		map<string, string>::const_iterator cit = mapHeaders.cbegin();
		while (cit != mapHeaders.cend())
		{
			if (cit->first.compare("Host") != 0)
				evhttp_add_header(evhttp_request_get_output_headers((struct evhttp_request *)reqRedirect), cit->first.c_str(), cit->second.c_str());
			cit++;
		}
		evhttp_add_header(evhttp_request_get_output_headers((struct evhttp_request *)reqRedirect), "Host", sHost.c_str());

		// 初始化请求路径
		struct evhttp_uri *decoded = evhttp_uri_parse(evhttp_request_get_uri((const struct evhttp_request *)m_req));
		string sPath = evhttp_uri_get_path(decoded);
		sPath += "?";
		sPath += evhttp_uri_get_query(decoded);

		if (decoded)
			evhttp_uri_free(decoded);

		// 发起请求
		evhttp_make_request(connRedirect, (struct evhttp_request *)reqRedirect, EVHTTP_REQ_POST, sPath.c_str());
		event_base_dispatch(baseRedirect);

		char *szBuf = get_input_buffer(reqRedirect);
		evhttp_connection_free(connRedirect);
		event_base_free(baseRedirect);

		// 返回数据
		if (szBuf)
		{
			// 获取range头
			map<string, string> mapHeader;
			if (!get_input_headers(reqRedirect, mapHeader))
			{
				delete[] szBuf;
				throw HttpRequestException(HTTP_BADREQUEST, "1", "redirect http don't have header.");
			}

			map<string, string>::iterator itRange = mapHeader.find("Range");
			if (itRange != mapHeader.end())
				evhttp_add_header(evhttp_request_get_output_headers((struct evhttp_request *)m_req), "Range", itRange->second.c_str());

			send_respond_success(szBuf);
			delete[] szBuf;
		}
		else
		{
			throw HttpRequestException(HTTP_INTERNAL, "1", "read respond data failed!");
		}
	}

	void Controller::http_request_done(struct evhttp_request *req, void *arg)
	{
		printf("send m_request ok...\n");
		size_t len = evbuffer_get_length(evhttp_request_get_input_buffer((struct evhttp_request *)req));
		unsigned char * str = evbuffer_pullup(evhttp_request_get_input_buffer((struct evhttp_request *)req), len);
		char buf[256] = { 0 };
		memcpy(buf, str, len);
		if (str == NULL)
		{
			printf("len = %d, str == NULL\n", len);
		}
		else
		{
			printf("len = %d, str = %s\n", len, buf);
		}

		event_base_loopbreak((struct event_base*)arg);
	}

	void Controller::send_respond(void *pBusiness)
	{
		B::Business *p = (B::Business*)pBusiness;
		if (p == NULL)
			return;
		evhttp_add_header(evhttp_request_get_output_headers((struct evhttp_request *)m_req), "Content-Type", "application/json");
		struct evbuffer *evb = evbuffer_new();
		string sReplyData = Json::FastWriter().write(p->respond_data());
		sReplyData = sReplyData.substr(0, sReplyData.length() - 1);
		evbuffer_add_printf(evb, "%s", sReplyData.c_str());
		printf("%d %s\n", p->http_status(), sReplyData.c_str());
		map<std::string, std::string>::iterator it = p->CustomHeaders().begin();
		while (it != p->CustomHeaders().end())
		{
			evhttp_add_header(evhttp_request_get_output_headers((struct evhttp_request *)m_req), it->first.c_str(), it->second.c_str());
			it++;
		}
		evhttp_send_reply((struct evhttp_request *)m_req, p->http_status(), "failed", evb);
		if (evb)
			evbuffer_free(evb);
	}
}