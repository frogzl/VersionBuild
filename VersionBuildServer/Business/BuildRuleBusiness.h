#pragma once
#include "Business.h"
namespace B
{
	class BuildRuleBusiness : public Business
	{
	public:
		BuildRuleBusiness(Controller::Controller *pController);
		~BuildRuleBusiness();
	};
}
