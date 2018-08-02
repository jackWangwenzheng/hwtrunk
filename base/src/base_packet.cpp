#include "base_packet.h"

CPacket::CPacket()
{
	m_UserDataMap.clear();
	m_headDataLen = sizeof(Clt_Head);
	m_recvFd = 0;
}

CPacket::~CPacket()
{
}

//epoll线程调用接收数据
int CPacket::onRecvData(int fd, void* recvBuf, int len)
{
	int n = 0;
	map<int, User*>::iterator iter = m_UserDataMap.find(fd);
	if (iter != m_UserDataMap.end())
	{
		iter->second->data.erase();
		n = iter->second->data.write(recvBuf, len);
		m_recvFd = fd;
	}
	return 0;
}

int CPacket::creatNewUser(int fd)
{	
	if (m_UserDataMap.find(fd) == m_UserDataMap.end())
	{
		cout << "new user" << endl;
		User* user = new User();
		user->data.erase();
		user->fd = fd;
		m_UserDataMap[fd] = user;
	}
}

int CPacket::deleteUser(int fd)
{
	if (m_UserDataMap.find(fd) == m_UserDataMap.end())
	{
		cout << "delete user" << endl;
		delete m_UserDataMap[fd];
		m_UserDataMap.erase(fd);
	}
}

int CPacket::unPacket()
{
	memset(m_buf, 0, 4096);   //这里需要做一个修改，公用容易出问题

	map<int, User*>::iterator iter = m_UserDataMap.find(m_recvFd);
	if ( iter != m_UserDataMap.end())
	{
		//CStream m_stream = m_UserDataMap[recvFd]->data; //没有加复制构造函数，这样直接赋值是不对的
		int mBufLen = iter->second->data.lenth();
		if(mBufLen < m_headDataLen) //缓冲区数据不够一个包头的数据
		{
			cout << "unpacket fail data not enough head length" << endl;
			iter->second->data.position(0); //解包失败，指针回到缓冲区头指针
			return -1;
		}
		iter->second->data.read(m_buf, m_headDataLen);
		Clt_Head* pClt = (Clt_Head*)m_buf;
		if(pClt->pack_start != PACKET_START)
		{
			cout << "packet start error" << endl;
		}

		if((mBufLen - m_headDataLen) < pClt->pack_len) //缓冲区的数据不够一个包体长度
		{
			cout << "unpacket fail data not enough body length" << endl;
			iter->second->data.position(0); //解包失败，指针回到缓冲区头指针
			return -2;
		}
		iter->second->data.read(m_buf, pClt->pack_len + m_headDataLen);
		iter->second->data.erase();		
	}
	return 0;
}

//处理收到的数据(解包线程调用)
int CPacket::waitRecvData()
{
	if (m_recvFd != 0)
	{
		AutoLock lock(&m_lock);
		//cout << "waitRecvData.."<< endl;
		if (unPacket() == 0)
		{
			test_msg* p = (test_msg*) m_buf;
			//p指向这个结构体
			cout<<"a:"<<p->a<<endl;
			//cout<<"b:"<<p->b<<endl;
			m_recvFd = 0;	
		}
	}
}

//解包线程
int CPacket::Run()
{
	cout << "CPacket start" << endl;
	while(GetbActive())
	{
		waitRecvData();
	}
	cout << "CPacket end" << endl;
}