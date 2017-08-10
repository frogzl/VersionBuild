#include "FinishTask.h"
#include "../Exception/HttpRequestException.h"
#include "../Tools/HttpClient.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Deploy.h"
#include "../Database/Resource_Host.h"
FinishTask::FinishTask(ServiceData *pD) :m_pD(pD)
{
}

FinishTask::~FinishTask()
{
}

void FinishTask::process_task()
{
}