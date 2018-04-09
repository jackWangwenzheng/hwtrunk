#ifndef _BASESOCKETSERVER_H_
#define _BASESOCKETSERVER_H_

class CSocketServer:public BaseThread
{
public:
	int BindSocket(const struct sockaddr); 
	int ListenScoket();
	int AcceptSocket();
	int RecvData();
	int SendData();
public:
	CSocketServer();
	~CSocketServer();

private:
	int socketFd;
};

#endif