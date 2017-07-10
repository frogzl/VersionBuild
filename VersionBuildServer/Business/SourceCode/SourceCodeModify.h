#pragma once
#include "../SourceCodeBusiness.h"
#include "../../Common.h"
namespace B
{
	class SourceCodeModify : public SourceCodeBusiness
	{
	public:
		SourceCodeModify(Controller::Controller *pController);
		~SourceCodeModify();

		void process_task();
		void background_process();
	};
}