#pragma once
#include "ServiceData.h"
class CreateCompilingToolInstance
{
	typedef struct
	{
		void *pData;
		std::string _sMsg;
	}CallBackData;
public:
	CreateCompilingToolInstance(ServiceData *pB);
	~CreateCompilingToolInstance();
	void process_task();
private:
	bool check_input_data();
private:
	ServiceData *m_pD;

	std::string _sCompilingToolID;
	std::string _sData;
};