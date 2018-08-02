#include"base_socket.h"

CSocket::CSocket()
{

}

CSocket::~CSocket()
{

}

// qlen 表示最大的未完成请求连接数量  alen表示地址的长度
int CSocket::initServer(int type, const struct sockaddr_in *addr, int alen, int qlen)
{
	int fd;
	int err = 0;
	if((fd = socket(addr->sin_family, type, 0)) < 0)
		return -1;

	if(bind(fd, (sockaddr *)addr, alen) < 0)
	{
		close(fd);
		return -1;
	}

	if(type == SOCK_STREAM || type == SOCK_SEQPACKET)
	{
		if(listen(fd, qlen) < 0)
		{
			close(fd);
			return -1;
		}
	}
	return fd;
}

int CSocket::accept(int fd, struct sockaddr_in * addr, socklen_t* alen)
{
	int clientFd = accept(fd, addr, alen);
	return clientFd;
}

int CSocket::shutDown(int fd, int how)
{
	int ret = shutdown(fd, how);
	return ret;
}

int CSocket::getScokName(int fd, struct sockaddr_in * addr, socklen_t* alen)
{
	int ret = getsockname(fd, (sockaddr *)addr, alen);
	return ret;
}

int CSocket::sendData(int fd, const void* buf, int nbytes)
{
	int slen = send(fd, buf, nbytes, 0);
	return slen;
}

int CSocket::recvData(int fd, void* buf, int nbytes)
{
	int rlen = recv(fd, buf, nbytes, 0);
	return rlen;
}