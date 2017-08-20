#pragma once
#include "ServiceData.h"

class DownloadBlock
{
public:
	DownloadBlock(ServiceData *pB);
	~DownloadBlock();
	void process_task();
private:
	bool check_input_data();
private:
	ServiceData *m_pD;

	std::string _sName;
	std::string _sIP;
};
