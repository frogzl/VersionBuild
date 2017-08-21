#pragma once
#include "ServiceData.h"
class Upload
{
	typedef struct
	{
		void *pData;
		std::string _sMsg;
	}CallBackData;
public:
	Upload(ServiceData *pB);
	~Upload();
	void process_task();
private:
	bool check_input_data();
private:
	ServiceData *m_pD;

	std::string _sStorageID;
	long long _llStart;
	long long _llEnd;
	long long _llTotal;
	std::string _sFileName;
};