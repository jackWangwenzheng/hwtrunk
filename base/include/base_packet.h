#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include "base_stream.h"
#include "base_thread.h"
#include "base_define.h"
#include "base_lock.h"
using namespace std;
struct test_msg
{
	int a;
	int b;
};
struct User
{
	CStream data;
	int fd;		
};
class CPacket: public BaseThread
{

public:
	CPacket();
	~CPacket();

public:
	int unPacket();  //解包
	int onRecvData(int fd, void* recvBuf, int len);    //写入数据
	int Run();

	int waitRecvData();
	int creatNewUser(int fd);
	int deleteUser(int fd);
private:
	uint32 m_headDataLen;
	char m_buf[4096];
	int m_recvFd;                  //收到数据的fd
	map<int, User*> m_UserDataMap; //玩家数据池
	BaseLock m_lock;
};

#endif