#include "stdafx.h"
#include "Http.h"
#include <algorithm>
namespace Helper
{
	namespace Network
	{
		Http::Http()
		{
			pBase = NULL;
			pConnection = NULL;
			pRequest = NULL;
		}

		Http::~Http()
		{
		}

		bool Http::post(HostType enHT, string sPluginID, string sPluginVersion, Request_Data &inData)
		{
			begin();
			append_header();
			append_data();
			request_send();
			end();
			//------------------------------------
			bool bRet = false;
			pBase = event_base_new();
			Item item;
			item.pBase = pBase;
			item.pHttp = this;
			pRequest = evhttp_request_new(http_request_done, &item);
			pConnection = evhttp_connection_base_new(pBase, NULL, sHost.c_str(), nPort);

			// 初始化头
			evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Host", sHost.c_str());
			evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Content-Type", "application/json");

			// 初始化请求路径
			char szUrl[255] = { 0 };
			sprintf(szUrl, "http://%s:%d%s", sHost.c_str(), nPort, sPath.c_str());

			// 设置数据
			evbuffer_add(evhttp_request_get_output_buffer(pRequest), (const void *)sData.c_str(), sData.size());

			// 发起请求
			evhttp_make_request(pConnection, pRequest, EVHTTP_REQ_POST, sPath.c_str());
			event_base_dispatch(pBase);

			// 返回数据
			if (m_nHttpCode == 200)
			{
				bRet = true;
			}
			else
			{
				m_sErrorCode = "1";
			}

			evhttp_request_free(pRequest);
			evhttp_connection_free(pConnection);
			event_base_free(pBase);
			return bRet;
		}

		bool Http::get(HostType enHT, string sPluginID, string sPluginVersion, Request_Data &inData)
		{
			begin();
			add_header();
			end();
			//------------------------------------
			bool bRet = false;
			pBase = event_base_new();
			Item item;
			item.pBase = pBase;
			item.pHttp = this;
			pRequest = evhttp_request_new(http_request_done, &item);
			pConnection = evhttp_connection_base_new(pBase, NULL, sHost.c_str(), nPort);

			// 初始化头
			evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Host", sHost.c_str());
			evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Content-Type", "application/json");

			// 初始化请求路径
			char szUrl[255] = { 0 };
			if (sParam.compare("") != 0)
				sprintf(szUrl, "http://%s:%d%s?%s", sHost.c_str(), nPort, sPath.c_str(), sParam.c_str());
			else
				sprintf(szUrl, "http://%s:%d%s", sHost.c_str(), nPort, sPath.c_str());

			// 发起请求
			evhttp_make_request(pConnection, pRequest, EVHTTP_REQ_GET, szUrl);
			event_base_dispatch(pBase);

			// 返回数据
			if (m_nHttpCode == 200)
			{
				bRet = true;
			}
			else
			{
				m_sErrorCode = "1";
			}

			evhttp_request_free(pRequest);
			evhttp_connection_free(pConnection);
			event_base_free(pBase);
			return bRet;
		}

		bool Http::upload(string sPluginID, string sPluginVersion, Request_Data &inData)
		{

		}

		bool Http::download(string sPluginID, string sPluginVersion, Request_Data &inData)
		{

		}


		void Http::http_request_done(struct evhttp_request *req, void *arg)
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
	}
}