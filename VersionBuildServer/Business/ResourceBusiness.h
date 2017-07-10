#pragma once
#include "Business.h"
	namespace B
{
	class ResourceBusiness : public Business
	{
	public:
		ResourceBusiness(Controller::Controller *pController);
		~ResourceBusiness();

		void background_process();
	};
}
