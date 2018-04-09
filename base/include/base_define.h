#ifndef _BASEDEFINE_
#define _BASEDEFINE_
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
typedef unsigned char uint8;
typedef unsigned int uint32;

#define MIDDLE_BUFF_SIZE 10240
#define MAX_BUFF_SIZE 102400
#define PACKET_START 0x0AAAAAAA
#define MIN_BUFF_SIZE	0x0800			//= 2K
#define CLT_BUFF_SIZE	0x02000			//= 8K
#define USR_BUFF_SIZE	0x04000			//= 16k
#define PCK_BUFF_SIZE	0x08000			//= 32k
#define APP_BUFF_SIZE	0x020000		//= 128K
#define APP2_BUFF_SIZE	0x040000		//= 256K
#define DAT_BUFF_SIZE	0x080000		//= 512K
#define SVR_BUFF_SIZE	0x0100000		//= 1M
#define SYS_BUFF_SIZE	0x010000		//= 64k

#define GATE_BUFF_SIZE 0x08000//32K

#pragma pack(1)
struct Clt_Head
{
	uint32 pack_start;	//��ʼ������֤�õ�
	uint32 pack_len;	//����С+cltnum*4
	uint32 pack_cmd;	//Э���
	uint32 pack_seqno;	//�����
	uint32 sessionid;	//��֤�ͻ��˺Ϸ���
};

struct  Svr_Head :public Clt_Head
{
	uint32 roleid;
	uint32 cltnum;
};

#define PCK_OFFSET (sizeof(Svr_Head) - sizeof(Clt_Head))

Clt_Head* SrvHeadToCltHead(char* pPack)
{
	Clt_Head* pCltHead = (Clt_Head*)(pPack+PCK_OFFSET);

	Clt_Head cmd = *(Clt_Head*)pPack;
	cmd.pack_len -= PCK_OFFSET;

	memmove(pCltHead, &cmd, sizeof(Clt_Head));
	return pCltHead;
};

Svr_Head* CltHeadToSrvHead(char* pPack)
{
	Svr_Head* pSvrHead = (Svr_Head*)(pPack - PCK_OFFSET);
	Clt_Head cmd = *(Clt_Head*)pPack;
	memmove(pSvrHead, &cmd, sizeof(Clt_Head));
	return pSvrHead;
};

#pragma pack()

#endif