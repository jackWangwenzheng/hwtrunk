#ifndef _BASE_SOCKETSERVER_H_
#define _BASE_SOCKETSERVER_H_

#include"base_util.h"
#include"base_epoll.h"
#include"base_thread.h"

class CSocketServer: public BaseThread
{	
public:
	CSocketServer();
	~CSocketServer();
public:
	int Run();
	void Init(int nIp, int nPort);

	bool DoRead(Event& e);
	bool DoWrite(Event& e);
	bool DoError(Event& e);

	void Send(int fd);
private:
	int m_listenfd;
	CEpoll m_epoll;
};

#endif