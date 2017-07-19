#pragma once
#include "include/ServiceInterface.h"

class B
{

};
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

	void destory();
	int route_infos(Route_Info *&routeInfos);
	const char* unique_id();	
	const char* name();
	const char* version();
	const char* dispatch_by_route_path(int nIndex, BusinessInterface *pB);

	bool register_service_name(const char *szName);
	bool register_service_unique_id(const char *szID);
	bool register_service_version(const char *szVersion);
	bool register_http_route(const char *szPath, const char *szOperation, FuncProcess pCallBack);

	bool change_to_fast_mode();
private:
	std::vector<Route_Info> *pVecTmpRI;  // 用于临时存储
	std::vector<FuncProcess> *pVecTmpFP; // 用于临时存储

	const char *szServiceName;
	const char *szServiceUniqueId;
	const char *szServiceVersion;

	int nRouteCount;
	Route_Info *riRouteInfos;
	FuncProcess *fpRoutesProcess;

	ObjectMode omObjectMode;
};