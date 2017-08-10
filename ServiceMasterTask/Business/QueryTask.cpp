#include "QueryTask.h"
#include "../Exception/HttpRequestException.h"
#include "../Common.h"
QueryTask::QueryTask(ServiceData *pD) :m_pD(pD)
{
}

QueryTask::~QueryTask()
{
}

void QueryTask::process_task()
{
}
