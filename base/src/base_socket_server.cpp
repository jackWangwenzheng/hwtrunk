#include "base_socket_server.h"

CSocketServer::CSocketServer()
{
}

CSocketServer::~CSocketServer()
{
}

int CSocketServer::Run()
{
    cout << "CSocketServer start" << endl;
    while(GetbActive())
    {
        struct Event ev[256];

        int n = m_epoll.EpollWait(ev);

        for(int i = 0;i<n;++i)
        {
            //cout << ev[i].fd << "," << ev[i].read << "," << ev[i].write << "," << ev[i].error << endl;
            cout << "continue num:" << n << endl;
            if(DoError(ev[i])) continue;

            if(DoRead(ev[i])) continue;

            if(DoWrite(ev[i])) continue;
        }
    }
    cout << "CSocketServer end" << endl;

    return 0;
}

void CSocketServer::Init(int nIP, int nPort, CPacket* packet)
{
    m_epoll.EpollCreate();
    
    sockaddr_in _sockaddr_in;
    _sockaddr_in.sin_family = AF_INET;
    _sockaddr_in.sin_addr.s_addr = nIP;
    _sockaddr_in.sin_port = htons(nPort);

    m_listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (bind(m_listenfd,(struct sockaddr*)&_sockaddr_in, sizeof(_sockaddr_in)) < 0)
    {
        printf("bind error\n");
        return;
    }

    if (listen(m_listenfd, 10) < 0)
    {
        printf("listen error\n");
        return;
    }

    m_epoll.EpollAdd(m_listenfd);
    m_packet = packet;
    cout << "CSocketServer Init:Port=" << nPort << ",listenfd=" << m_listenfd << endl;
}

bool CSocketServer::DoWrite(Event& e)
{
    if(e.write)
    {
        //send的事情
    }   
    return false;
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
            cout << "a new connection and fd:" << clientFd << endl;
            if (clientFd < 0)
            {
                printf("accept clientFd error\n");
                return false;
            }
            m_epoll.EpollAdd(clientFd);
            m_packet->creatNewUser(clientFd);
            return true;
        }
        else 
        {
            for(;;)
            {
                int n = 0;
                static char buff[4096];
                {
                    AutoLock lock(&m_lock);
                    memset(buff,0,sizeof(buff));
                    n = recv(e.fd, buff, sizeof(buff), MSG_DONTWAIT);
                     //int n = recv(e.fd, buff, sizeof(buff), 0); //这种是阻塞模式，接受数据后会阻塞，等待下一个数据的到来，这样会阻塞整个线程
                }

                if(n>0)
                {
                    //cout << "recv,n=" << n << ",buff:"<< buff << endl;
                    m_packet->onRecvData(e.fd, buff, n);
                }
                else
                {
                    if((n == 0) || errno != EAGAIN || errno != EWOULDBLOCK)
                    {
                        cout << "errno:" << errno << endl;
                        m_epoll.EpollDel(e.fd);
                        close(e.fd);
                        return true;
                    }
                    //cout << "n=" << n <<",errno=" << errno << endl;
                    break;    
                }
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
        return true;
    }
    return false;
}

//逻辑线程B在调用你这个函数
void CSocketServer::Send(int fd)
{
    m_epoll.EpollWrite(fd,NULL,true);
}