#pragma once
#include <vector>
#include "HttpServerItem.h"

class HttpServer
{
public:
	HttpServer(int nItems);
	~HttpServer();
public:
	void start(int nPort, int nBackLog);
	void wait_for_end();
	void stop();
private:
	SOCKET bind_socket(int port, int backlog);
private:
	std::vector<HttpServerItem*> m_vecItems;
};

