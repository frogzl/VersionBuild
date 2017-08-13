#pragma once
#include "Task.h"
class ProcessingCenter
{
public:
	ProcessingCenter();
	~ProcessingCenter();

	static bool add_processing_item(Task *pTask);
private:
	static void process(void *pParam);
};

