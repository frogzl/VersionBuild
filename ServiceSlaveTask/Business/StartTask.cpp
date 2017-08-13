#include "StartTask.h"
#include "../Exception/HttpRequestException.h"
#include "../PluginCenter.h"
#include "../ProcessingCenter.h"
StartTask::StartTask(ServiceData *pD) :m_pD(pD)
{
}

StartTask::~StartTask()
{
}

void StartTask::process_task()
{
	string sPath = m_pD->request_data().jData["task_path"].asString();
	Task *pTask = PluginCenter::parse_task_path(sPath.c_str());
	if (pTask)
	{
		if (ProcessingCenter::add_processing_item(pTask))
			m_pD->set_respond_back(499, "1", "start task failed", "");
		else
			m_pD->set_respond_back(HTTP_OK, "0", "successed", "");
	}
	else
		m_pD->set_respond_back(499, "1", "no matching task", sPath);
}