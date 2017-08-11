#include "StartTask.h"
#include "../Exception/HttpRequestException.h"
#include "../Tools/HttpClient.h"

StartTask::StartTask(ServiceData *pD) :m_pD(pD)
{
}

StartTask::~StartTask()
{
}

void StartTask::process_task()
{
}