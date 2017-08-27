#pragma once
#include "ServiceData.h"
#include "../Common.h"
class UploadBlock
{
	typedef struct
	{
		void *pData;
		std::string _sMsg;
	}CallBackData;
public:
	UploadBlock(ServiceData *pB);
	~UploadBlock();
	void process_task();
private:
	bool check_input_data();
	ULONGLONG get_dir_free_size(string sDirName);
private:
	ServiceData *m_pD;

	std::string _sStorageID;
	ULONGLONG _llStart;
	ULONGLONG _llEnd;
	ULONGLONG _llTotal;
	std::string _sFileName;
};