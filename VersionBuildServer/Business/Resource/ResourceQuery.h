#pragma once
#include "../ResourceBusiness.h"
#include "../../Common.h"
namespace B
{
	class ResourceQuery : public ResourceBusiness
	{
	public:
		ResourceQuery(Controller::Controller *pController);
		~ResourceQuery();

		void process_task();
		void background_process();
	};
}