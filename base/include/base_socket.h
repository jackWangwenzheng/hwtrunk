#ifndef _BASE_SOCKET_H_
#define _BASE_SOCKET_H_
#include "base_util.h"

class CSocket
{
public:
	//封装的时候，可以参考一下unix环境编程的490页的方式
	//sendto函数也可以考虑封装进去，反正后面的人可能会用（发送报文的协议）
	//做几个地址相关的处理函数

	int initServer(int type, const struct sockaddr_in *addr, int alen, int qlen);   //初始化服务器
	int accept(int fd, struct sockaddr_in* addr, socklen_t* alen);
	int shutDown(int fd, int how);                                           //关闭某个方向的数据传输或者双向的数据传输
	int recvData(int fd, void* buf, int nbytes);                    //接收数据
	int sendData(int fd, const void* buf, int nbytes);                    //发送数据
	int getScokName(int fd, struct sockaddr_in * addr, socklen_t* alen);

public:
	CSocket();
	~CSocket();
};

#endif