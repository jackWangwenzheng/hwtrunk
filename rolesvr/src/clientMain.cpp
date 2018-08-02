#include <iostream>
#include <vector>
#include <pthread.h>      
#include <netdb.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h> 
#include <string.h>
#include <strings.h>
using namespace std;
// int main()  
// {  
//     int socket_fd;  
//     struct sockaddr_in server_addr;  
//     char message[1024];

//    if( (socket_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 ) 
//     {  
//         printf("create socket error: %s(errno:%d)\n)",strerror(errno),errno);  
//         exit(0);  
//     }  

//     memset(&server_addr,0,sizeof(server_addr));
//     server_addr.sin_addr.s_addr = htons(INADDR_ANY);  
//     server_addr.sin_family = AF_INET;  
//     server_addr.sin_port = htons(8000);  

//     if( connect(socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0 ) 
//     {  
//         printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
//         exit(0);  
//     }  

//     printf("send message to server: \n");
//     while(1)
//     {
//         memset(message,0,sizeof(message));
//         fgets(message,sizeof(message),stdin);  

//         if( send( socket_fd,message,strlen(message),0 ) <= 0 ) 
//         {  
//             printf("send message error\n");  
//             exit(0);  
//         }       
//     }
 

//     close(socket_fd);  
//     exit(0);  
//     return 0;  
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////
struct test_msg
{
    int a;
    int b;
};

typedef unsigned int uint32;
struct Clt_Head
{
    uint32 pack_start;  //开始符，验证用的
    uint32 pack_len;    //包大小+cltnum*4
    uint32 pack_cmd;    //协议号
    uint32 pack_seqno;  //包编号
    uint32 sessionid;   //验证客户端合法性
};

int main()  
{  
packet1:
    int clientNum = 0;
    cout << "please input connect client num:" << endl;
    cin >> clientNum;
    std::vector<int> v_fds;  
    for (int i = 0; i < clientNum; ++i)
    {
        int socket_fd;  
        struct sockaddr_in server_addr;  

       if( (socket_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 ) 
        {  
            printf("create socket error: %s(errno:%d)\n)",strerror(errno),errno);  
            exit(0);  
        }  

        memset(&server_addr,0,sizeof(server_addr));
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);  
        server_addr.sin_family = AF_INET;  
        server_addr.sin_port = htons(8000);  

        if( connect(socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0 ) 
        {  
            printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
            exit(0);  
        }  

        printf("send message to server: \n");
        Clt_Head head;
        head.pack_start = 0x0AAAAAAA;
        head.pack_len = 256;
        head.pack_cmd = 111;
        head.pack_seqno = 1000;
        head.sessionid = 1001;
        int head_len = sizeof(head);

        test_msg message;
        message.a = 1;
        message.b = 2;
        int message_len = 256;
        static char* m_Buff = new char[head_len + message_len];


        memset(m_Buff,0,head_len + message_len);
        memcpy(m_Buff,&head,head_len);
        memcpy(&m_Buff[head_len],&message,message_len);

        if( send(socket_fd, m_Buff,(head_len + message_len),0 ) <= 0 ) 
        {  
            printf("send message error\n");  
            exit(0);  
        }  
        v_fds.push_back(socket_fd);
        cout << "clientNum:" << i <<endl;
    }

    int is_end = 0;
    cout << "do you want end this? end cin 1, not cin 0" << endl;
    cin >> is_end; 
    if (is_end == 1) 
    {
        std::vector<int>::iterator it;
        for (it=v_fds.begin();it!=v_fds.end();it++)
        {
            close(*it);  
        }
        exit(0);  
        return 0; 
    }
    else
    {
        goto packet1;
    }
}