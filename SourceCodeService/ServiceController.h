#pragma once
class ServiceController
{
public:
	typedef struct
	{
		char *szPath;
		char *szoperation;
	}Route_Info;

	typedef struct 
	{
	}Request_Data;

	typedef struct
	{
	}Respond_Data;

public:
	ServiceController();
	~ServiceController();

	string route_infos();
	string unique_id();
	string name();
	string version();
	string dispatch_by_route_path(char *szRoutePath, char *sz, Request_Data &inData, Respond_Data &outData);
private:
	Route_Info *routeInfos;
	int nRouteInfoCnt;
};

