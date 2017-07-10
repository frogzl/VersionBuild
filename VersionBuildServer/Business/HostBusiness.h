#pragma once
#include "Business.h"
namespace B
{

	class HostBusiness : public Business
	{
	public:
		HostBusiness(Controller::Controller *pController);
		~HostBusiness();

		void background_process();
	};
}
