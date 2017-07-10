#pragma once
#include "Common.h"

class VBTaskServer
{
public:
	VBTaskServer();
	~VBTaskServer();
public:
	void start();
	void stop();

	void wait_for_end();
private:
	static void processing_dispatch_callback(void *arg);
	static void summary_dispatch_ccallback(void *arg);
private:
	HANDLE m_hThreadProcessing;
	HANDLE m_hThreadSummary;
};

