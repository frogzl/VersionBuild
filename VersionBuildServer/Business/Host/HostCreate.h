#pragma once
#include "../HostBusiness.h"
#include "../../Common.h"
namespace B
{

	class HostCreate : public HostBusiness
	{
	public:
		HostCreate(Controller::Controller *pController);
		~HostCreate();

		void process_task();
		void background_process();

	};
}