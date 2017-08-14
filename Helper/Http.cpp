#include "stdafx.h"
#include "Http.h"
#include "SystemConfig.h"
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

		bool Http::post(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData)
		{
			if (begin(enHT))
			{
				append_header(inData.mHeaders);
				append_data(inData.sData);
				string sRoute = "/" + sPluginID + "/" + sPluginVersion + sPath;
				request_send(EVHTTP_REQ_POST, sRoute, inData.mConditions);
				end();
				return true;
			}
			else
				return false;
		}

		bool Http::get(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData)
		{
			if (begin(enHT))
			{
				append_header(inData.mHeaders);
				string sRoute = "/" + sPluginID + "/" + sPluginVersion + sPath;
				request_send(EVHTTP_REQ_GET, sRoute, inData.mConditions);
				end();
				return true;
			}
			else
				return false;
		}

		bool Http::upload(string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, string sLocalPath)
		{
			bool bRet = true;
			Json::Value *pJData = new Json::Value();
			(*pJData)["filename"] = sFileName;
			(*pJData)["storagepartid"] = "";
			(*pJData)["path"] = sRemotePath;

			long long llBlock = 10 * 1024 * 1024;
			long long llStart = 0;
			char *szBuf = new char[llBlock + 1];
			while (true)
			{
				memset(szBuf, 0, llBlock + 1);
				FILE *fp = fopen(sLocalPath.c_str(), "rb");
				if (!fp)
				{
					bRet = false;
					break;
				}
				fseek(fp, llStart, SEEK_SET);
				int nRead = fread(szBuf, llBlock, 1, fp);
				fclose(fp);
				if (nRead != 0 && begin(enReverseProxy))
				{
					(*pJData)["data"] = Base64_Encode(szBuf, nRead);
					string sData = Json::FastWriter().write((*pJData));
					append_header(inData.mHeaders);
					append_data(sData);
					string sRoute = "/" + sPluginID + "/" + sPluginVersion + sPath;
					request_send(EVHTTP_REQ_POST, sRoute, inData.mConditions);
					end();
					if (nRead < llBlock)
						break;
					else
					{
						llStart += nRead;
					}
				}
				else
				{
					bRet = false;
					break;
				}
			}
			return bRet;
		}

		bool Http::download(string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, string sLocalPath)
		{

		}


		void Http::http_request_done(struct evhttp_request *req, void *arg)
		{
			printf("send m_request ok...\n");
			Http*pItem = (Http*)arg;
			if (req == NULL)
			{
				pItem->set_http_code(0);
				return;
			}
			pItem->set_http_code(evhttp_request_get_response_code(req));
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
					pItem->set_http_respond_data(m_inputData);
				printf("len = %d, str = %s\n", len, szBuf);
				delete[] szBuf;
			}

			event_base_loopbreak((struct event_base*)pItem->pBase);
		}

		bool Http::begin(HostType enHT)
		{
			pBase = event_base_new();
			if (enHT == enReverseProxy)
			{
				_sIP = SystemConfig::instance()->_sRPSIP;
				_nPort = SystemConfig::instance()->_nRPSPort;
			}
			if (enHT == enGuard)
			{
				_sIP = SystemConfig::instance()->_sGSIP;
				_nPort = SystemConfig::instance()->_nGSPort;
			}
			if (pBase)
				pConnection = evhttp_connection_base_new(pBase, NULL, _sIP.c_str(), _nPort);
			pRequest = evhttp_request_new(http_request_done, this);
			if (pBase && pConnection && pRequest)
				return true;
			return false;
		}

		bool Http::append_header(map<string, string> &mHeaders)
		{
			evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Host", _sIP.c_str());
			evhttp_add_header(evhttp_request_get_output_headers(pRequest), "Content-Type", "application/json");
			map<string, string>::iterator it = mHeaders.begin();
			while (it != mHeaders.end())
			{
				evhttp_add_header(evhttp_request_get_output_headers(pRequest), it->first.c_str(), it->second.c_str());
				it++;
			}
			return true;
		}

		bool Http::append_data(string &sData)
		{
			evbuffer_add(evhttp_request_get_output_buffer(pRequest), (const void *)sData.c_str(), sData.size());
			return true;
		}

		bool Http::request_send(evhttp_cmd_type type, string &sRoute, map<string, string> &mConditions)
		{
			char szUrl[255] = { 0 };
			sprintf(szUrl, "http://%s:%d%s", _sIP.c_str(), _nPort, sRoute.c_str());
			string sUrl = szUrl;
			if (mConditions.size() > 0)
			{
				sUrl += "?";
				map<string, string>::iterator it = mConditions.begin();
				while (true)
				{
					sUrl += (it->first + "=" + it->second);
					it++;
					if (it != mConditions.end())
						sUrl += "&";
					else
						break;
				}
			}
			// ·¢ÆðÇëÇó
			evhttp_make_request(pConnection, pRequest, type, szUrl);
			event_base_dispatch(pBase);
			return true;
		}

		bool Http::end()
		{
			evhttp_request_free(pRequest);
			evhttp_connection_free(pConnection);
			event_base_free(pBase);
			return true;
		}

	}
}