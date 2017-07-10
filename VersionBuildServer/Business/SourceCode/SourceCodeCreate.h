#pragma once
#include "../SourceCodeBusiness.h"
#include "../../Common.h"
namespace B
{
	class SourceCodeCreate : public SourceCodeBusiness
	{
	public:
		SourceCodeCreate(Controller::Controller *pController);
		~SourceCodeCreate();

		void process_task();
		void background_process();
	};
}