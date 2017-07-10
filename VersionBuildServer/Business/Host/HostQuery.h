#pragma once
#include "../HostBusiness.h"
#include "../../Common.h"
namespace B
{

	class HostQuery : public HostBusiness
	{
	public:
		HostQuery(Controller::Controller *pController);
		~HostQuery();

		void process_task();
		void background_process();
	};
}