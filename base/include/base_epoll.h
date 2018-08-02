#ifndef _BASEEPOLL_H_
#define _BASEEPOLL_H_

#define MAX 1024

#include"base_util.h"

struct Event
{	
	int fd;
	bool read;
	bool write;
	bool error;
};

class CEpoll
{
public:
	int EpollCreate()
	{
		epollFd = epoll_create(MAX);
		if(epollFd == -1)
		{
			printf("EpollCreate fail");
		}
	}

	int EpollAdd(int fd)
	{
		struct epoll_event ev;
		ev.events=EPOLLIN|EPOLLET;
		ev.data.fd = fd;
		int ret = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev);
		return ret;
	}

	int EpollWait( struct Event* ev )
	{
		struct epoll_event monitorEv[MAX];
		int nfds = epoll_wait(epollFd, monitorEv, MAX, -1);
		for (int i = 0; i < nfds; ++i)
		{
			(ev+i)->fd = monitorEv[i].data.fd;	
			
			(ev+i)->read = false;
			(ev+i)->write = false;
			(ev+i)->error = false;
			
			if(monitorEv[i].events&EPOLLIN)
			{
				(ev+i)->read = true;
			}
			else if(monitorEv[i].events&EPOLLOUT)
			{
				(ev+i)->write = true;
			}
			else if(monitorEv[i].events&EPOLLERR)
			{
				(ev+i)->error = true;
			}
		}
		return nfds;
	}

	void EpollDel(int sock)	
	{
		int ret = epoll_ctl(epollFd, EPOLL_CTL_DEL, sock , NULL);
		if(ret < 0)
		{
			printf("EpollDel fail");
		}
	}

	void EpollWrite(int sock, void *ud, bool enable)
	{
		struct epoll_event ev;
		ev.events = EPOLLIN | (enable ? EPOLLOUT : 0);
		ev.data.fd = sock;
		int ret = epoll_ctl(epollFd, EPOLL_CTL_MOD, sock, &ev);
		if(ret < 0)
		{
			printf("EpollWrite fail");
		}		
	}

public:
	CEpoll()
	{
	};
	~CEpoll()
	{
		close(epollFd);
	};

private:
	int epollFd;
};

#endif