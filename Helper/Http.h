#pragma once
#include "HelperTypes.h"
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
				struct event_base* pBase;
				Http *pHttp;
			}Item;
		public:
			Http();
			~Http();
			bool post(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData);
			bool get(HostType enHT, string sPluginID, string sPluginVersion, string sPath, Request_Data &inData);
			bool upload(string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, string sLocalPath);
			bool download(string sPluginID, string sPluginVersion, string sPath, Request_Data &inData, string sLocalPath);
			Respond_Data& Respond() { return _rd; }

		private:
			static void http_request_done(struct evhttp_request *req, void *arg);

			bool begin(HostType enHT);
			bool append_header(map<string, string> &mHeaders);
			bool append_data(string &sData);
			bool request_send(evhttp_cmd_type type, string &sRoute, map<string, string> &mConditions);
			bool end();
		private:
			struct event_base* pBase;
			struct evhttp_connection* pConnection;
			struct evhttp_request* pRequest;
			string _sIP;
			int _nPort;

			Respond_Data _rd;
		};
	}
}