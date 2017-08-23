#pragma once
#include "ServiceData.h"
class QueryCompilingToolInstance
{
	typedef struct
	{
		void *pData;
		std::string _sMsg;
	}CallBackData;
public:
	QueryCompilingToolInstance(ServiceData *pB);
	~QueryCompilingToolInstance();
	void process_task();
private:
	ServiceData *m_pD;
};