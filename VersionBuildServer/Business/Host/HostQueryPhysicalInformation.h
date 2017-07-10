#pragma once
#include "../HostBusiness.h"
#include "../../Common.h"
namespace B
{

class HostQueryPhysicalInformation : public HostBusiness
{
public:
	HostQueryPhysicalInformation(Controller::Controller *pController);
	~HostQueryPhysicalInformation();

	void process_task();
	void background_process();
private:
	Json::Value getOperatingSystem();
	Json::Value getCPU();
	Json::Value getMemory();
	Json::Value getStorage();
	Json::Value getEnvironmentVariable();
};
}