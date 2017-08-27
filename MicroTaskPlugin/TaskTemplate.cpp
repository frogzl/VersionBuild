#include "TaskTemplate.h"
#include "TaskDataTemplate.h"
TaskTemplate::TaskTemplate()
{
	nRouteCount = -1;
	riRouteInfos = NULL;
	fpTaskCreateProcess = NULL;
	omObjectMode = enTemplate;
	pVecTmpRI = new vector<Task_Route_Info>;
	pVecTmpFP = new vector<FuncTaskProcess>;
}

TaskTemplate::~TaskTemplate()
{
	if (fpTaskCreateProcess)
		delete [] fpTaskCreateProcess;
	if (riRouteInfos)
		delete [] riRouteInfos;

	if (pVecTmpRI)
		delete pVecTmpRI;
	if (pVecTmpFP)
		delete pVecTmpFP;

	pVecTmpRI = NULL;
	pVecTmpFP = NULL;
	fpTaskCreateProcess = NULL;
	riRouteInfos = NULL;
}

void TaskTemplate::destory()
{
	delete this;
}

int TaskTemplate::route_infos(Task_Route_Info *&routeInfos)
{
	return 0;
}

const char* TaskTemplate::unique_id()
{
	return szTaskUniqueId;
}

const char* TaskTemplate::name()
{
	return szTaskName;
}

const char* TaskTemplate::version()
{
	return szTaskVersion;
}

const char* TaskTemplate::library_version()
{
	return "0.1";
}

TaskData* TaskTemplate::create_data()
{
	return new TaskDataTemplate();
}

bool TaskTemplate::dispatch_by_route_path(int nIndex, TaskData *pTD)
{
	if (nIndex >= 0 && nIndex < nRouteCount)
	{
		fpTaskCreateProcess[nIndex](pTD);
		return true;
	}
	else
		return false;
}

bool TaskTemplate::register_task_name(const char *szName)
{
	szTaskName = szName;
	return true;
}

bool TaskTemplate::register_task_unique_id(const char *szID)
{
	szTaskUniqueId = szID;
	return true;
}


bool TaskTemplate::register_task_version(const char *szVersion)
{
	szTaskVersion = szVersion;
	return true;
}

bool TaskTemplate::register_task_route(const char *szPath, FuncTaskProcess pCallBack)
{
	Task_Route_Info tri;
	tri.nIndex = (int)pVecTmpFP->size();
	tri.szPath = szPath;
	pVecTmpRI->push_back(tri);
	pVecTmpFP->push_back(pCallBack);
	return true;
}

bool TaskTemplate::change_to_fast_mode()
{
	if (omObjectMode == enInstantiation)
		return true;
	if (pVecTmpRI->size() != pVecTmpFP->size())
		return false;

	nRouteCount = (int)pVecTmpRI->size();
	if (nRouteCount > 0)
	{
		riRouteInfos = new Task_Route_Info[nRouteCount];
		fpTaskCreateProcess = new FuncTaskProcess[nRouteCount];
		for (int nIndexRI = 0; nIndexRI < nRouteCount; nIndexRI++)
			riRouteInfos[nIndexRI] = (*pVecTmpRI)[nIndexRI];
		for (int nIndexFP = 0; nIndexFP < nRouteCount; nIndexFP++)
			fpTaskCreateProcess[nIndexFP] = (*pVecTmpFP)[nIndexFP];
	}
	delete pVecTmpRI;
	pVecTmpRI = NULL;

	omObjectMode = enInstantiation;
	return true;
}