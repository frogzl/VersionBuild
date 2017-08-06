#include "HttpServer.h"


HttpServer::HttpServer(int nItems)
{
	for (int nIndex = 0; nIndex < nItems; nIndex++)
		m_vecItems.push_back(new HttpServerItem());
}


HttpServer::~HttpServer()
{
}

void HttpServer::start(int nPort, int nBackLog)
{
	SOCKET s = bind_socket(nPort, nBackLog);
	if (s < 0) 
		return;
	for (int nIndex = 0; nIndex < (int)m_vecItems.size(); nIndex++)
		m_vecItems[nIndex]->start(s);
}

void HttpServer::wait_for_end()
{
	for (int nIndex = 0; nIndex < (int)m_vecItems.size(); nIndex++)
	{
		WaitForSingleObject(m_vecItems[nIndex]->thread_handle(), INFINITE);
	}
}

void HttpServer::stop()
{
	for (int nIndex = 0; nIndex < (int)m_vecItems.size(); nIndex++)
		m_vecItems[nIndex]->stop();
}

SOCKET HttpServer::bind_socket(int port, int backlog)
{
	int r;
	SOCKET m_Socket;
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket < 0) return -1;

	int one = 1;
	r = setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	r = bind(m_Socket, (struct sockaddr*)&addr, sizeof(addr));
	if (r < 0) return -1;

	r = listen(m_Socket, backlog);
	if (r < 0) return -1;

	unsigned long ul = 1;
	ioctlsocket(m_Socket, FIONBIO, (unsigned long *)&ul);

	return m_Socket;
}
