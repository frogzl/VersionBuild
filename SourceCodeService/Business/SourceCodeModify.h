#pragma once
#include "../Business.h"
class SourceCodeModify : public Business
{
public:
	SourceCodeModify();
	~SourceCodeModify();

	void process_task();
	void background_process();
};