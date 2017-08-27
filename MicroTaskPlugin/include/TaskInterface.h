#pragma once
#include "TaskData.h"

typedef struct
{
	const char *szPath;					// 路由模板
	int nIndex;							// 索引
}Task_Route_Info;

class TaskInterface
{
public:
	virtual ~TaskInterface();
	// 自销毁
	virtual void destory() = 0;
	// 用于获取路由信息
	virtual int route_infos(Task_Route_Info *&routeInfos) = 0;
	// 用于获取唯一标识
	virtual const char* unique_id() = 0;
	// 用于获取服务名
	virtual const char* name() = 0;
	// 用于获取插件实现库的版本
	virtual const char* version() = 0;
	// 用于获取插件基础库的版本
	virtual const char* library_version() = 0;
	// 创建数据接口
	virtual TaskData* create_data() = 0;
	// 用于根据API执行
	virtual bool dispatch_by_route_path(int nIndex, TaskData *pTD) = 0;
	// 注册服务名
	virtual bool register_task_name(const char *szName) = 0;
	// 注册服务唯一标识
	virtual bool register_task_unique_id(const char *szID) = 0;
	// 注册服务版本号
	virtual bool register_task_version(const char *szVersion) = 0;
	// 注册路由
	virtual bool register_task_route(const char *szPath, FuncTaskProcess pCallBack) = 0;
};