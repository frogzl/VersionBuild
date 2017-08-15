#include "CreateTask.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/SourceCode_Deploy.h"
#include "../Database/BuildRule.h"
#include "../Database/BuildRule_Deploy.h"
#include "../Database/Resource_SourceCode.h"
#include "../Database/Resource_Host.h"

CreateTask::CreateTask(ServiceData *pD) :m_pD(pD)
{
}

CreateTask::~CreateTask()
{
}

void CreateTask::process_task()
{

}

bool CreateTask::check_inputdata(string &sFailedDetail)
{
	/*
	name
	head
	size
	clone_url
	*/
	if (m_pD->request_data().jData["name"].asString().compare("") == 0)
	{
		sFailedDetail = "name is missing";
		return false;
	}

	if (m_pD->request_data().jData["head"].asString().compare("") == 0)
	{
		sFailedDetail = "head is missing";
		return false;
	}

	if (m_pD->request_data().jData["clone_url"].asString().compare("") == 0)
	{
		sFailedDetail = "clone_url is missing";
		return false;
	}
	return true;
}