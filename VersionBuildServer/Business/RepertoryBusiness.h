#pragma once
#include "Business.h"
namespace B
{
	class RepertoryBusiness : public Business
	{
	public:
		RepertoryBusiness(Controller::Controller *pController);
		~RepertoryBusiness();

		void background_process();
	};
}
