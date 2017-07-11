#pragma once
#include "ServiceController.h"
class SourceCodeController : public ServiceController
{
public:
	SourceCodeController();
	~SourceCodeController();

protected:
	void register_http_routes();
	string unique_id();
	string name();
	string version();
	string dispatch_by_route_path(char *szRoutePath, char *sz, Request_Data &inData, Respond_Data &outData);
};

