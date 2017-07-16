#pragma once
#include "../Business.h"

	class SourceCodeBuild : public Business
	{
	public:
		SourceCodeBuild();
		~SourceCodeBuild();

		void process_task();
		void background_process();
	private:
		bool check_inputdata(string &sFailedDetail);
		void* get_buildrule_host(string sDeployid);
	};
