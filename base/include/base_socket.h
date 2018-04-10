#ifndef _BASE_SOCKET_H_
#define _BASE_SOCKET_H_

class CSocket
{
public:
	// int BindSocket(const struct sockaddr); 
	// int ListenScoket();
	// int AcceptSocket();
	// int RecvData();
	// int SendData();
public:
	CSocket();
	~CSocket();

private:
	int socketFd;
};

#endif