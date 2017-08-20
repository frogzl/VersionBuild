#pragma once
#include "include/HelperTypes.h"
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_compat.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

namespace Helper
{
	namespace Network
	{
		class Http
		{
			typedef struct
			{
				long long llStart;
				long long llEnd;
				long long llTotle;
				string sLocalPath;
			}DownloadParam;
		public:
			Http();
			~Http();
			bool post(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData);
			bool post(HostType enHT, string sUrl, Request_Data &inData);
			bool get(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData);
			bool get(HostType enHT, string sUrl, Request_Data &inData);
			bool upload(string sPluginID, string sPluginVersion, string sPath, string sLocalPath);
			bool download(string sPluginID, string sPluginVersion, string sPath, string sLocalPath);
			bool download_block(string sPluginID, string sPluginVersion, string sPath, int nStart, int nCount, char *szBuf);
			Respond_Data& Respond() { return *_rd; }

		private:
			static void http_request_done(struct evhttp_request *req, void *arg);
			static bool http_analytical_upload_response(Respond_Data *_rd, void *arg);
			static bool http_analytical_download_response(Respond_Data *_rd, void *arg);
			static bool http_analytical_download_response2(Respond_Data *_rd, void *arg);

			bool http_begin(HostType enHT);
			bool http_append_headers(map<string, string> &mHeaders);
			bool http_append_header(string sName, string sValue);
			bool http_append_data(string &sData);
			bool http_request_send(evhttp_cmd_type type, 
				string &sRoute, 
				map<string, string> *pMConditions, 
				bool(*cb)(Respond_Data *, void *), void *arg);
			bool http_end();
		private:
			struct event_base *_pBase;
			struct evhttp_connection *_pConnection;
			struct evhttp_request *_pRequest;
			string _sIP;
			int _nPort;
			long long _llBlock;

			Respond_Data *_rd;
		};
	}
}