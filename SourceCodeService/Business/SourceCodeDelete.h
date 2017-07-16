#pragma once
#include "../Business.h"
class SourceCodeDelete : public Business
{
public:
	SourceCodeDelete();
	~SourceCodeDelete();

	void process_task();
	void background_process();
};
