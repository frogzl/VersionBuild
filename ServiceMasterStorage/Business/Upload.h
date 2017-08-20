#pragma once
#include "ServiceData.h"
#include "Helper.h"
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
	void create_first_block();
	static bool process_task_callback(Helper::Network::Respond_Data *pData, void*);
private:
	ServiceData *m_pD;

	std::string _sStorageID;
	long long _llStart;
	long long _llEnd;
	long long _llTotal;
	std::string _sFileName;
};