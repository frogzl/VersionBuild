#pragma once

class TaskInterface
{
public:
	virtual ~TaskInterface();
	// 自销毁
	virtual void destory() = 0;
	// 用于获取路由信息
	virtual int route_infos(Route_Info *&routeInfos) = 0;
	// 用于获取唯一标识
	virtual const char* unique_id() = 0;
	// 用于获取服务名
	virtual const char* name() = 0;
	// 用于获取版本
	virtual const char* version() = 0;
	// 用于根据API执行
	virtual const char* dispatch_by_route_path(int nIndex, BusinessInterface *pB) = 0;
	// 注册服务名
	virtual bool register_service_name(const char *szName) = 0;
	// 注册服务唯一标识
	virtual bool register_service_unique_id(const char *szID) = 0;
	// 注册服务版本号
	virtual bool register_service_version(const char *szVersion) = 0;
	// 注册路由
	virtual bool register_http_route(const char *szPath, const char *szOperation, FuncProcess pCallBack) = 0;
};

