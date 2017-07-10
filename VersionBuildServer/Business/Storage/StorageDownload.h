#pragma once
#include "../StorageBusiness.h"
namespace B
{
	class StorageDownload : public StorageBusiness
	{
	public:
		StorageDownload(Controller::Controller *pController);
		~StorageDownload();

		void process_task();
		void background_process();
	};
}