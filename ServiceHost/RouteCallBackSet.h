#pragma once
#include "ServiceData.h"
class RouteCallBackSet
{
public:
	// 添加主机
	static void create_host(ServiceData *pD);

	// 查询主机
	static void query_host(ServiceData *pD);

	// 删除主机
	static void delete_host(ServiceData *pD);

	// 修改主机
	static void modify_host(ServiceData *pD);

	// 查询可执行角色
	static void query_executable_role(ServiceData *pD);

	// 添加可执行角色的部署信息
	static void create_executable_role_deployment_information(ServiceData *pD);

	// 查询可执行角色的部署信息
	static void query_executable_role_deployment_information(ServiceData *pD);

	// 修改可执行角色的部署信息
	static void modify_executable_role_deployment_information(ServiceData *pD);

	// 删除可执行角色的部署信息
	static void delete_executable_role_deployment_information(ServiceData *pD);

};

