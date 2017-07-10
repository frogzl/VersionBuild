#pragma once
#include "../SourceCodeBusiness.h"
#include "../../Common.h"
	namespace B
{
	class SourceCodeDelete : public SourceCodeBusiness
	{
	public:
		SourceCodeDelete(Controller::Controller *pController);
		~SourceCodeDelete();

		void process_task();
		void background_process();
	};
}