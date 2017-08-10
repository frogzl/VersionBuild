#pragma once
#include "include/TaskInterface.h"
#include <json/json.h>
#include <vector>
using namespace std;
class TaskTemplate : public TaskInterface
{
	enum ObjectMode
	{
		enTemplate,
		enInstantiation
	};
public:
	TaskTemplate();
	~TaskTemplate();

	void destory();
	int route_infos(Task_Route_Info *&routeInfos);
	const char* unique_id();
	const char* name();
	const char* version();
	const char* library_version();
	TaskData* create_data();
	const char* dispatch_by_route_path(int nIndex, TaskData *pTD);
	bool register_task_name(const char *szName);
	bool register_task_unique_id(const char *szID);
	bool register_task_version(const char *szVersion);
	bool register_task_route(const char *szPath, FuncTaskProcess pCallBack);

	bool change_to_fast_mode();
private:
	vector<Task_Route_Info> *pVecTmpRI;  // 用于临时存储
	vector<FuncTaskProcess> *pVecTmpFP; // 用于临时存储

	const char *szTaskName;
	const char *szTaskUniqueId;
	const char *szTaskVersion;


	int nRouteCount;
	Task_Route_Info *riRouteInfos;
	FuncTaskProcess *fpTaskCreateProcess;

	ObjectMode omObjectMode;
};

