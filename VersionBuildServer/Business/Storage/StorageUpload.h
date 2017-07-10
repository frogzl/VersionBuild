#pragma once
#include "../StorageBusiness.h"
	namespace B
{
	class StorageUpload : public StorageBusiness
	{
	public:
		StorageUpload(Controller::Controller *pController);
		~StorageUpload();

		void process_task();
		void background_process();
	};
}