#pragma once
#include <string>
using namespace std;
class ServiceController
{
public:
	typedef struct
	{
		const char *szPath;					// 路由模板
		const char *szoperation;			// http 操作
		const char *szBusinessName;	// 处理对象名
		int nIndex;						// 索引
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

	int route_infos(Route_Info *&routeInfos);
protected:
	/*
	 * 支持注册的http操作类型
	 * GET				请求获取Request-URI所标识的资源
	 * POST			在Request-URI所标识的资源后附加新的数据
	 * HEAD			请求获取由Request-URI所标识的资源的响应消息报头
	 * PUT				请求服务器存储一个资源，并用Request-URI作为其标识
	 * DELETE			请求服务器删除Request-URI所标识的资源
	 * TRACE			请求服务器回送收到的请求信息，主要用于测试或诊断
	 * OPTIONS		请求查询服务器的性能，或者查询与资源相关的选项和需求
	 */
	bool register_http_get(const char *szPath, const char *szBusinessName);
	bool register_http_http_post(const char *szPath, const char *szBusinessName);
	bool register_http_head(const char *szPath, const char *szBusinessName);
	bool register_http_put(const char *szPath, const char *szBusinessName);
	bool register_http_delete(const char *szPath, const char *szBusinessName);
	bool register_http_trace(const char *szPath, const char *szBusinessName);
	bool register_http_options(const char *szPath, const char *szBusinessName);

	/*
	 * 初始化要注册的路由个数，需要在register_http_routes接口的最开始调用
	 */
	bool init_route_count(int nCount);

protected: // interface
	virtual void register_http_routes() = 0;
	virtual string unique_id() = 0;
	virtual string name() = 0;
	virtual string version() = 0;
	virtual string dispatch_by_route_path(char *szRoutePath, char *sz, Request_Data &inData, Respond_Data &outData) = 0;

private:
	bool register_http_route(const char *szPath, const char *szBusinessName, const char *szOperation);

private:
	Route_Info *riRouteInfos;
	int nRouteInfoCnt;
	int nRouteInfoIndex;
};

