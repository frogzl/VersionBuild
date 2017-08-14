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
		public:
			bool post(HostType enHT, string sPluginID, string sPluginVersion, Request_Data &inData);
			bool get(HostType enHT, string sPluginID, string sPluginVersion, Request_Data &inData);
			bool upload(string sPluginID, string sPluginVersion, Request_Data &inData);
			bool download(string sPluginID, string sPluginVersion, Request_Data &inData);
			Respond_Data& Respond() { return _rd; }
		private:
			static void http_request_done(struct evhttp_request *req, void *arg);
		private:
			struct event_base* pBase;
			struct evhttp_connection* pConnection;
			struct evhttp_request* pRequest;

			Respond_Data _rd;
		};
	}
}