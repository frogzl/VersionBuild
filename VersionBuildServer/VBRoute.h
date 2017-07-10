#pragma once
#include "Common.h"

class VBRoute
{
private:
	VBRoute();
public:
	~VBRoute();
public:
	static void dispatch(struct evhttp_request *req);
	static void post(const char *szPath, const char *szClassName, const char *szOperator);
	static void get(const char *szPath, const char *szClassName, const char *szOperator);
private:
	static void call_band_function(const char *szPath, struct evhttp_request *req);
private:
	static std::map<std::string, std::string> m_mapPostRoutes;
	static std::map<std::string, std::string> m_mapGetRoutes;
};

