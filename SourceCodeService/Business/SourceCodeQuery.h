#pragma once
#include "../Business.h"

class SourceCodeQuery : public Business
{
public:
	SourceCodeQuery();
	~SourceCodeQuery();

	void process_task();
	void background_process();
};
