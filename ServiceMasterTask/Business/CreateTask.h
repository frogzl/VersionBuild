#pragma once
#include "ServiceData.h"

class CreateTask
{
public:
	CreateTask(ServiceData *pB);
	~CreateTask();
	void process_task();
private:

	bool check_inputdata(std::string &sFailedDetail);
	ServiceData *m_pD;
};
