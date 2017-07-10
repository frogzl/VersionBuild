#include "VBRoute.h"
#include "Common.h"
#include "VBController.h"

using namespace Controller;
map<string, string> VBRoute::m_mapPostRoutes;
map<string, string> VBRoute::m_mapGetRoutes;
VBRoute::VBRoute()
{
}


VBRoute::~VBRoute()
{
}

void VBRoute::dispatch(struct evhttp_request *req)
{
	const char *uri = evhttp_request_get_uri(req);
	struct evhttp_uri *decoded = evhttp_uri_parse(uri);
	if (!decoded) 
	{
		printf("It's not a good URI.\n");
		evhttp_send_error(req, HTTP_BADREQUEST, "It's not a good URI.");
		return;
	}

	call_band_function(evhttp_uri_get_path(decoded), req);
	if (decoded)
		evhttp_uri_free(decoded);
}

void VBRoute::post(const char *szPath, const char *szClassName, const char *szOperator)
{
	string s = szClassName;
	s += "@";
	s += szOperator;
	m_mapPostRoutes.insert(pair<string, string>(szPath, s));
}

void VBRoute::get(const char *szPath, const char *szClassName, const char *szOperator)
{
	string s = szClassName;
	s += "@";
	s += szOperator;
	m_mapGetRoutes.insert(pair<string, string>(szPath, s));
}

void VBRoute::call_band_function(const char *szPath, struct evhttp_request *req)
{
	printf("URL:%s\n", szPath);
	map<string, string>::const_iterator cit;
	switch (evhttp_request_get_command(req))
	{
	case EVHTTP_REQ_GET: 
	{
		cit = m_mapGetRoutes.find(szPath);
		if (cit != m_mapGetRoutes.end())
		{
			if (!VBController::call_function(cit->second, req))
			{
				char szLog[100];
				sprintf(szLog, "Controller %s not found.\n", cit->second.c_str());
				printf("%s", szLog);
				evhttp_send_error(req, HTTP_BADREQUEST, szLog);
				return;
			}
		}
		else
		{
			printf("It's not a registered URI.\n");
			evhttp_send_error(req, HTTP_BADREQUEST, "It's not a registered URI.");
			return;
		}
		break;
	}
	case EVHTTP_REQ_POST: 
	{	
		cit = m_mapPostRoutes.find(szPath);
		if (cit != m_mapPostRoutes.end())
		{
			if (!VBController::call_function(cit->second, req))
			{
				char szLog[100];
				sprintf(szLog, "Controller %s not found.\n", cit->second.c_str());
				printf("%s", szLog);
				evhttp_send_error(req, HTTP_BADREQUEST, szLog);
				return;
			}
		}
		else
		{
			printf("It's not a registered URI.\n");
			evhttp_send_error(req, HTTP_BADREQUEST, "It's not a registered URI.");
			return;
		}

		break;
	}
	default: 
		printf("Your operator type is not supported.\n");
		evhttp_send_error(req, HTTP_BADMETHOD, "Your operator type is not supported.");
		return;
	}
}