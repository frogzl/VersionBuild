#pragma once
#include "../StorageBusiness.h"
	namespace B
{
	class StorageUploadPart : public StorageBusiness
	{
	public:
		StorageUploadPart(Controller::Controller *pController);
		~StorageUploadPart();

		void process_task();
		void background_process();
	};
}