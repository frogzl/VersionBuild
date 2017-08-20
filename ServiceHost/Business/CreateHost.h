#pragma once
#include "ServiceData.h"

class CreateHost
{
public:
	CreateHost(ServiceData *pB);
	~CreateHost();
	void process_task();
private:
	bool check_input_data();
private:
	ServiceData *m_pD;

	std::string _sName;
	std::string _sIP;
};
