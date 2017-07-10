#pragma once
#include "../BuildRuleBusiness.h"
#include "../../Common.h"
namespace B
{
	class BuildRuleQuery : public BuildRuleBusiness
	{
	public:
		BuildRuleQuery(Controller::Controller *pController);
		~BuildRuleQuery();

		void process_task();
		void background_process();
	};
}