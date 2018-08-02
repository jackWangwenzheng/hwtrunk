#ifndef _BASE_SOCKETSERVER_H_
#define _BASE_SOCKETSERVER_H_

#include "base_epoll.h"
#include "base_socket.h"
#include "base_thread.h"
#include "base_packet.h"

using namespace std;

class CSocketServer: public BaseThread
{	
public:
	CSocketServer();
	~CSocketServer();
public:
	int Run();
	void Init(int nIp, int nPort, CPacket* packet);

	bool DoRead(Event& e);
	bool DoWrite(Event& e);
	bool DoError(Event& e);

	void Send(int fd);
private:
	int m_listenfd;
	CEpoll m_epoll;
	CSocket m_socket;
	CPacket* m_packet;
	BaseLock m_lock;
};

#endif