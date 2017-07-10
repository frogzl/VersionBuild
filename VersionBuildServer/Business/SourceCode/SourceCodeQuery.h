#pragma once
#include "../SourceCodeBusiness.h"
#include "../../Common.h"
namespace B
{
	class SourceCodeQuery : public SourceCodeBusiness
	{
	public:
		SourceCodeQuery(Controller::Controller *pController);
		~SourceCodeQuery();

		void process_task();
		void background_process();
	};
}