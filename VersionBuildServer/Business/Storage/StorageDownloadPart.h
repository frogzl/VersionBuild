#pragma once
#include "../StorageBusiness.h"
	namespace B
{
	class StorageDownloadPart : public StorageBusiness
	{
	public:
		StorageDownloadPart(Controller::Controller *pController);
		~StorageDownloadPart();

		void process_task();
		void background_process();
	};
}