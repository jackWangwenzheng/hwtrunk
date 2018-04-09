#ifndef _BASESOCKET_H_
#define _BASESOCKET_H_

class CSocket
{
public:
	int BindSocket(const struct sockaddr); 
	int ListenScoket();
	int AcceptSocket();
	int RecvData();
	int SendData();
public:
	CSocket();
	~CSocket();

private:
	int socketFd;
};

#endif