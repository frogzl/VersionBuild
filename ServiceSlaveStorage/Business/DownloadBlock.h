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

	std::string _sPath;
	long long _llStart;
	long long _llEnd;
};
