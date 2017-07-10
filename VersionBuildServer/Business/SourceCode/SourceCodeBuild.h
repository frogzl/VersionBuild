#pragma once
#include "../SourceCodeBusiness.h"
#include "../../Common.h"
#include "../../Database/Resource_Host.h"
namespace B
{
	class SourceCodeBuild : public SourceCodeBusiness
	{
	public:
		SourceCodeBuild(Controller::Controller *pController);
		~SourceCodeBuild();

		void process_task();
		void background_process();
	private:
		bool check_inputdata(string &sFailedDetail);
		DB::Resource_HostData* get_buildrule_host(string sDeployid);
	};
}