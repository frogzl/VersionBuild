#pragma once
#include "ServiceData.h"

class AddBuildRule
{
public:
	AddBuildRule(ServiceData *pD);
	~AddBuildRule();
	void process_task();
private:
	bool check_inputdata();
private:
	ServiceData *m_pD;

	std::string _sSourceCodeID;
	int _nInnerID;
	int _nAutoBuild;
	std::string _sProxyHostID;
	std::string _sServerHostID;
	std::string _sTargetFileName;
	std::string _sTargetFilePath;
	std::string _sCompileToolInsID;
	std::string _sOutputDirectoryTemplate;
};
