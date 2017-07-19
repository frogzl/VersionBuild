#pragma once
#include "BusinessInterface.h"
#define Http_Operator_Get			"get"		//	请求获取Request - URI所标识的资源
#define Http_Operator_Post			"post"		//	在Request - URI所标识的资源后附加新的数据
#define Http_Operator_Head			"head"		//	请求获取由Request - URI所标识的资源的响应消息报头
#define Http_Operator_Put			"put"		//	请求服务器存储一个资源，并用Request - URI作为其标识
#define Http_Operator_Delete		"delete"	//	请求服务器删除Request - URI所标识的资源
#define Http_Operator_Trace			"trace"		// 请求服务器回送收到的请求信息，主要用于测试或诊断
#define Http_Operator_Options		"options"	//	请求查询服务器的性能，或者查询与资源相关的选项和需求

typedef struct
{
	const char *szPath;					// 路由模板
	const char *szoperation;			// http 操作
	int nIndex;							// 索引
}Route_Info;

class ServiceInterface
{
public:

public:
	virtual ~ServiceInterface();
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

