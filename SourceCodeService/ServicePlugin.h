#pragma once
#include "ServiceTemplate.h"
class ServicePlugin:public ServiceTemplate
{
protected:
	/*
	* 初始化要注册的路由个数，需要在register_http_routes接口的最开始调用
	*/
	bool init_route_count(int nCount);

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
	bool register_http_post(const char *szPath, const char *szBusinessName);
	bool register_http_head(const char *szPath, const char *szBusinessName);
	bool register_http_put(const char *szPath, const char *szBusinessName);
	bool register_http_delete(const char *szPath, const char *szBusinessName);
	bool register_http_trace(const char *szPath, const char *szBusinessName);
	bool register_http_options(const char *szPath, const char *szBusinessName);

	/*
	* 注册服务名
	*/
	bool register_service_name(const char *szName);

	/*
	* 注册服务唯一标识
	*/
	bool register_service_unique_id(const char *szID);

	/*
	* 注册服务版本号
	*/
	bool register_service_version(const char *szVersion);

	/*
	* 注册业务工厂
	*/
	bool register_service_business_factory(BusinessFactoryTpl *pFactory);
};

