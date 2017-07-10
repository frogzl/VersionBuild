#pragma once
#include "../SourceCodeBusiness.h"
#include "../../Common.h"
namespace B
{
	class SourceCodeDeploy : public SourceCodeBusiness
	{
	public:
		SourceCodeDeploy(Controller::Controller *pController);
		~SourceCodeDeploy();

		void process_task();
		void background_process();
	};
}