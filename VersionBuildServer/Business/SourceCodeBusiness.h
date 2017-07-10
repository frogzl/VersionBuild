#pragma once
#include "Business.h"
namespace B
{
	class SourceCodeBusiness : public Business
	{
	public:
		SourceCodeBusiness(Controller::Controller *pController);
		~SourceCodeBusiness();
	};
}
