#pragma once
#include "Business.h"
	namespace B
{
	class StorageBusiness : public Business
	{
	public:
		StorageBusiness(Controller::Controller *pController);
		~StorageBusiness();
	};
}
