#include "base_socket_server.h"

CSocketServer::CSocketServer()
{
}

CSocketServer::~CSocketServer()
{
}

int CSocketServer::Run()
{
    while(GetbActive())
    {
        struct Event ev[256];

        int n = m_epoll.EpollWait(ev);

        for(int i = 0;i<n;++i)
        {
            if(DoError(ev[i])) continue;

            if(DoRead(ev[i])) continue;

            if(DoWrite(ev[i])) continue;
        }
    }
}

void CSocketServer::Init(int nIP, int nPort)
{
    m_epoll.EpollCreate();
    
    sockaddr_in _sockaddr_in;
    _sockaddr_in.sin_family = AF_INET;
    _sockaddr_in.sin_addr.s_addr = nIP;
    _sockaddr_in.sin_port = htons(nPort);

    m_listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    bind(m_listenfd,(struct sockaddr*)&_sockaddr_in, sizeof(_sockaddr_in));

    listen(m_listenfd, 10);

    m_epoll.EpollAdd(m_listenfd);
}

bool CSocketServer::DoWrite(Event& e)
{
    if(e.write)
    {
        //send的事情
    }   
    return true;
}

bool CSocketServer::DoRead(Event& e)
{
    if(e.read)
    {
        if(e.fd == m_listenfd) //有新的连接进来
        {
            socklen_t clilen;
            struct sockaddr_in clientaddr;
            int clientFd = accept(m_listenfd, (sockaddr *)&clientaddr, &clilen);
            m_epoll.EpollAdd(clientFd);
        }
        else 
        {
            char buff[1024];
            int n = recv(e.fd, buff, sizeof(buff), MSG_DONTWAIT);

            if(n>0)
            {

            }else
            {
                //error
                m_epoll.EpollDel(e.fd);
                close(e.fd);
                return true;
            }
        }
    }
    return false;
}

bool CSocketServer::DoError(Event& e)
{
    if(e.error)
    {
         m_epoll.EpollDel(e.fd);
        close(e.fd);
    }
    return true;
}

//逻辑线程B在调用你这个函数
void CSocketServer::Send(int fd)
{
    m_epoll.EpollWrite(fd,NULL,true);
}