#include "base_include.h"

CSocketServer::CSocketServer()
{
	socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

CSocketServer::~CSocketServer()
{
	closesocket(socketFd);
}

int CSocketServer::BindSocket(const struct sockaddr)
{
    //绑定套接字  
    int retVal = bind(socketFd, &sockaddr, sizeof(sockaddr));  
    if(SOCKET_ERROR == retVal)  
    {     
        cout << "bind failed!" << endl;  
        closesocket(socketFd);   //关闭套接字  
        WSACleanup();           //释放套接字资源;  
        return -1;  
    }
    return retVal;
}

int CSocketServer::ListenSocket()
{
    int retVal = listen(socketFd, 1);  
    if(SOCKET_ERROR == retVal)  
    {  
        cout << "listen failed!" << endl;         
        closesocket(socketFd);   //关闭套接字  
        WSACleanup();           //释放套接字资源;  
        return -1;  
    }  
    return retVal;
}

int CSocketServer::AcceptSocket()
{
    sockaddr_in addrClient;  
    int addrClientlen = sizeof(addrClient);  
    sClient = accept(socketFd,&addrClient, &addrClientlen);  
    if(INVALID_SOCKET == sClient)  
    {  
        cout << "accept failed!" << endl;         
        closesocket(socketFd);   //关闭套接字  
        WSACleanup();           //释放套接字资源;  
        return -1;  
    }
    return sClient; 	
}
