#pragma once
#include <vector>
#include "VBHttpServerItem.h"

class VBHttpServer
{
public:
	VBHttpServer(int nItems);
	~VBHttpServer();
public:
	void start(int nPort, int nBackLog);
	void wait_for_end();
	void stop();
private:
	SOCKET bind_socket(int port, int backlog);
private:
	std::vector<VBHttpServerItem*> m_vecItems;
};

