#include "base_include.h"

CSocket::CSocket()
{
	socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

CSocket::~CSocket()
{
	close(socketFd);
}

int CSocket::BindSocket(const struct sockaddr)
{
    //绑定套接字  
    int retVal = bind(socketFd, &sockaddr, sizeof(sockaddr));  
    if(SOCKET_ERROR == retVal)  
    {     
        cout << "bind failed!" << endl;  
        close(socketFd);   //关闭套接字  
        return -1;  
    }
    return retVal;
}

int CSocket::ListenSocket()
{
    int retVal = listen(socketFd, 1);  
    if(SOCKET_ERROR == retVal)  
    {  
        cout << "listen failed!" << endl;         
        close(socketFd);   //关闭套接字  
        return -1;      
    }  
    return retVal;
}

int CSocket::AcceptSocket()
{
    sockaddr_in addrClient;  
    int addrClientlen = sizeof(addrClient);  
    sClient = accept(socketFd,&addrClient, &addrClientlen);  
    if(INVALID_SOCKET == sClient)  
    {  
        cout << "accept failed!" << endl;         
        close(socketFd);   //关闭套接字  
        return -1;  
    }
    return sClient; 	
}
