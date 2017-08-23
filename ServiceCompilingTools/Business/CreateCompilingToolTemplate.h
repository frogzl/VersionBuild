#pragma once
#include "ServiceData.h"

class CreateCompilingToolTemplate
{
public:
	CreateCompilingToolTemplate(ServiceData *pB);
	~CreateCompilingToolTemplate();
	void process_task();
private:
	bool check_input_data();
private:
	ServiceData *m_pD;

	std::string _sName;
	std::string	_sDataTemplate;
	std::string	_sCompileCmdTemplate;
};
