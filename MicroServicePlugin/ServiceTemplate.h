#pragma once
#include "ServiceInterface.h"
#include <json/json.h>
#include "BusinessFactory.h"
class ServiceTemplate : public ServiceInterface
{
	enum ObjectMode
	{
		enTemplate,
		enInstantiation
	};
public:
	ServiceTemplate();
	~ServiceTemplate();

	int route_infos(Route_Info *&routeInfos);
	const char* unique_id();
	const char* name();
	const char* version();
	const char* dispatch_by_route_path(int nIndex, Business::Request_Data &inData, Business::Respond_Data &outData);

	bool register_service_name(const char *szName);
	bool register_service_unique_id(const char *szID);
	bool register_service_version(const char *szVersion);
	bool register_http_route(const char *szPath, const char *szOperation, const char *szBusinessName, FuncCreate pCallBack);

	bool change_to_fast_mode();
private:
	vector<Route_Info> *pVecTemp;

	BusinessFactory *bf;
	Route_Info *riRouteInfos;
	const char *szServiceName;
	const char *szServiceUniqueId;
	const char *szServiceVersion;

	ObjectMode omObjectMode;
};

