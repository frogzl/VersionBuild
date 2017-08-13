#include "Task.h"

Task::Task()
{
}


Task::~Task()
{
}

bool Task::process()
{
	return pPlugin->dispatch(nCreateIndex, pData);
}

TaskData* Task::data()
{
	return pData;
}