#pragma once
#include "Business.h"
class ServiceInterface
{
public:
	typedef struct
	{
		const char *szPath;					// 路由模板
		const char *szoperation;			// http 操作
		const char *szBusinessName;	// 处理对象名
		int nIndex;								// 索引
	}Route_Info;
	void destory();
	const char* library_version();
public:
	virtual ~ServiceInterface();
	// 用于获取路由信息
	virtual int route_infos(Route_Info *&routeInfos) = 0;
	// 用于获取唯一标识
	virtual const char* unique_id() = 0;
	// 用于获取服务名
	virtual const char* name() = 0;
	// 用于获取版本
	virtual const char* version() = 0;
	// 用于根据API执行
	virtual const char* dispatch_by_route_path(int nIndex, Business::Request_Data &inData, Business::Respond_Data &outData) = 0;
};

