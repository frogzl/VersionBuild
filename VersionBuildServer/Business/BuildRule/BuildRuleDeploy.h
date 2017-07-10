#pragma once
#include "../BuildRuleBusiness.h"
#include "../../Common.h"
namespace B
{
	class BuildRuleDeploy : public BuildRuleBusiness
	{
	public:
		BuildRuleDeploy(Controller::Controller *pController);
		~BuildRuleDeploy();

		void process_task();
		void background_process();

	private:
		string get_sourcecode_name(string &sData);
		void init_depend_data_to_local(string &sDependResultID, string &sStoragePath);
	};
}