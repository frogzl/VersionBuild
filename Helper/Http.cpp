#include "stdafx.h"
#include "Http.h"
#include "SystemConfig.h"
#include <algorithm>
#include "Common.h"
namespace Helper
{
	namespace Network
	{
		Http::Http()
		{
			_pBase = NULL;
			_pConnection = NULL;
			_pRequest = NULL;
			_rd = NULL;
			_llBlock = 10 * 1024 * 1024;
		}

		Http::~Http()
		{
			if (_rd)
				free(_rd);
		}

		bool Http::post(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData)
		{
			string sRoute = "/" + sPluginID + "/" + sPluginVersion + sPath;
			return post(enHT, sRoute, inData);
		}

		bool Http::post(HostType enHT, string sUrl, Request_Data &inData)
		{
			if (http_begin(enHT))
			{
				http_append_headers(inData.mHeaders);
				http_append_data(inData.sData);
				http_request_send(EVHTTP_REQ_POST, sUrl, &(inData.mConditions), NULL);
				http_end();
				return true;
			}
			else
				return false;
		}

		bool Http::get(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData)
		{
			string sRoute = "/" + sPluginID + "/" + sPluginVersion + sPath;
			return get(enHT, sRoute, inData);

		}

		bool Http::get(HostType enHT, string sUrl, Request_Data &inData)
		{
			if (http_begin(enHT))
			{
				http_append_headers(inData.mHeaders);
				http_request_send(EVHTTP_REQ_GET, sUrl, &(inData.mConditions), NULL);
				http_end();
				return true;
			}
			else
				return false;
		}

		bool Http::upload(string sPluginID, string sPluginVersion, string sPath, string sLocalPath)
		{
			string sStorageID = "";
			Json::Value *pJData = new Json::Value();
			sLocalPath = replace_all_distinct(sLocalPath, "\\", "/");
			(*pJData)["filename"] = sLocalPath.substr(sLocalPath.rfind('/'));

			// 获取文件大小
			bool bRet = false;
			FILE *fp = fopen(sLocalPath.c_str(), "rb");
			if (fp)
			{
				fseek(fp, 0, SEEK_END);
				long llTotle = ftell(fp);
				fclose(fp);

				long long llStart = 0;
				char *szBuf = new char[_llBlock + 1];
				while (true)
				{
					memset(szBuf, 0, _llBlock + 1);
					FILE *fp = fopen(sLocalPath.c_str(), "rb");
					if (fp)
					{
						fseek(fp, llStart, SEEK_SET);
						size_t stRead = fread(szBuf, _llBlock, 1, fp);
						fclose(fp);
						if (stRead != 0 && http_begin(enReverseProxy))
						{
							(*pJData)["storagepartid"] = sStorageID;
							// 设置range头
							char szRange[255];
							sprintf(szRange, "bytes %ld-%ld/%ld", llStart, stRead, llTotle);
							http_append_header("range", szRange);

							// 设置数据
							(*pJData)["data"] = Base64_Encode(szBuf, stRead);
							string sData = Json::FastWriter().write((*pJData));
							http_append_data(sData);

							// 发起请求
							string sRoute = "/" + sPluginID + "/" + sPluginVersion + sPath;
							if (!http_request_send(EVHTTP_REQ_POST, sRoute, NULL, http_analytical_upload_response, &sStorageID))
							{
								http_end();
								break;
							}
							http_end();

							if (stRead < _llBlock)
							{
								bRet = true;
								break;
							}
							else
								llStart += stRead;
						}
						else
						{
							bRet = true;
							break;
						}
					}
				}
				delete[] szBuf;
			}
		
			delete pJData;
			return bRet;
		}

		bool Http::download(string sPluginID, string sPluginVersion, string sPath, string sLocalPath)
		{
			string sFileName = "";
			Json::Value *pJData = new Json::Value();
			sLocalPath = replace_all_distinct(sLocalPath, "\\", "/");

			long long llStart = 0;
			long long llEnd = _llBlock;
			long long llTotle = 0;
			bool bRet = false;
			while (true)
			{
				if (http_begin(enReverseProxy))
				{
					// 设置range头
					char szRange[255];
					sprintf(szRange, "bytes %ld-%ld/%ld", llStart, llEnd, llTotle);
					http_append_header("range", szRange);

					// 发起请求
					DownloadParam dlParam;
					dlParam.sLocalPath = sLocalPath;
					string sRoute = "/" + sPluginID + "/" + sPluginVersion + sPath;
					if (!http_request_send(EVHTTP_REQ_GET,
						sRoute,
						NULL,
						http_analytical_download_response,
						&dlParam))
					{
						http_end();
						break;
					}
					if (llEnd == llTotle)
					{
						http_end();
						bRet = true;
						break;
					}

					llStart = dlParam.llEnd;
					llEnd = llStart + _llBlock;
					llTotle = dlParam.llTotle;

					http_end();
				}
				else
				{
					break;
				}
			}
			delete pJData;
			return bRet;
		}

		void Http::http_request_done(struct evhttp_request *req, void *arg)
		{
			Http*pItem = (Http*)arg;
			if (req)
			{
				pItem->_rd->nHttpStatus = evhttp_request_get_response_code(req);
				size_t len = evbuffer_get_length(evhttp_request_get_input_buffer(req));
				unsigned char * str = evbuffer_pullup(evhttp_request_get_input_buffer(req), len);
				if (str == NULL)
				{
					pItem->_rd->sData = "";
				}
				else
				{
					char *szBuf = new char[len + 1];
					memset(szBuf, 0, len + 1);
					memcpy(szBuf, str, len);
					pItem->_rd->sData = szBuf;
					delete[] szBuf;

					struct evkeyvalq *headers;
					struct evkeyval *header;
					headers = evhttp_request_get_input_headers(req);
					for (header = headers->tqh_first; header; header = header->next.tqe_next)
						pItem->_rd->mHeaders.insert(pair<string, string>(header->key, header->value));
				}
			}
			else
			{
				pItem->_rd->nHttpStatus = 0;
				pItem->_rd->sData = "";
			}
			event_base_loopbreak((struct event_base*)pItem->_pBase);
		}

		bool Http::http_analytical_upload_response(Respond_Data *rd, void *arg)
		{
			string &sStorageID = *(string*)arg;
			if (rd->nHttpStatus == 200)
			{
				Json::Value *pRJData = new Json::Value();
				Json::Reader reader;
				if (reader.parse(rd->sData.c_str(), *pRJData))
				{
					sStorageID = (*pRJData)["storagepartid"].asString();
					delete pRJData;
					return true;
				}
				else
				{
					delete pRJData;
					return false;
				}
			}
			else
				return false;
		}

		bool Http::http_analytical_download_response(Respond_Data *rd, void *arg)
		{
			string &sLocalPath = *(string*)arg;
			if (rd->nHttpStatus == 200)
			{
				Json::Value *pRJData = new Json::Value();
				Json::Reader reader;
				if (reader.parse(rd->sData.c_str(), *pRJData))
				{
					Base64_Decode(sLocalPath.c_str(), "ab", (*pRJData)["data"].asString().c_str(), (*pRJData)["data"].asString().length());
					delete pRJData;
					return true;
				}
				else
				{
					delete pRJData;
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		bool Http::http_begin(HostType enHT)
		{
			_pBase = event_base_new();
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
			if (_pBase)
				_pConnection = evhttp_connection_base_new(_pBase, NULL, _sIP.c_str(), _nPort);
			_pRequest = evhttp_request_new(http_request_done, this);
			if (_pBase && _pConnection && _pRequest)
			{
				evhttp_add_header(evhttp_request_get_output_headers(_pRequest), "Host", _sIP.c_str());
				evhttp_add_header(evhttp_request_get_output_headers(_pRequest), "Content-Type", "application/json");
				if (_rd)
					free(_rd);
				_rd = (Respond_Data*)malloc(sizeof(Respond_Data));
				return true;
			}
			return false;
		}

		bool Http::http_append_headers(map<string, string> &mHeaders)
		{
			map<string, string>::iterator it = mHeaders.begin();
			while (it != mHeaders.end())
			{
				evhttp_add_header(evhttp_request_get_output_headers(_pRequest), it->first.c_str(), it->second.c_str());
				it++;
			}
			return true;
		}

		bool Http::http_append_header(string sName, string sValue)
		{
			evhttp_add_header(evhttp_request_get_output_headers(_pRequest), sName.c_str(), sValue.c_str());
			return true;
		}

		bool Http::http_append_data(string &sData)
		{
			evbuffer_add(evhttp_request_get_output_buffer(_pRequest), (const void *)sData.c_str(), sData.size());
			return true;
		}

		bool Http::http_request_send(evhttp_cmd_type type, 
			string &sRoute, 
			map<string, string> *pMConditions, 
			bool(*cb)(Respond_Data *, void *), void *arg)
		{
			char szUrl[255] = { 0 };
			sprintf(szUrl, "http://%s:%d%s", _sIP.c_str(), _nPort, sRoute.c_str());
			string sUrl = szUrl;

			if (pMConditions && pMConditions->size() > 0)
			{
				sUrl += "?";
				map<string, string>::iterator it = pMConditions->begin();
				while (true)
				{
					sUrl += (it->first + "=" + it->second);
					it++;
					if (it != pMConditions->end())
						sUrl += "&";
					else
						break;
				}
			}
			// 发起请求
			evhttp_make_request(_pConnection, _pRequest, type, szUrl);
			event_base_dispatch(_pBase);

			if (cb)
				return cb(_rd, arg);
			return true;
		}

		bool Http::http_end()
		{
			evhttp_request_free(_pRequest);
			evhttp_connection_free(_pConnection);
			event_base_free(_pBase);
			
			return true;
		}

	}
}