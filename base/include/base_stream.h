#ifndef _BASESTREAM_H
#define _BASESTREAM_H

class CStream
{
public:
	CStream(uint32 nSize = MIN_BUFF_SIZE);
	~CStream();
public:
	template <typename T> 
	inline T*& writeHeadInStream(const T& head)
	{
		uint32 nsize = sizeof(head);
		write(&head, nsize);
		return (T*&)m_Buff[0];
	}
	
	template<typename T>
	inline T*& NewHead()
	{
		m_Buff.resize(position() + sizeof(T));
		uint32 npos = position();
		//placement new
		T*& pNewHead = new(&m_Buff[npos])T();
		return pNewHead;
	}
	uint8& operator[](uint32 nindex);
	uint32 write(void* src,uint32 nsize);
	uint32 read(void* buff,uint32 nsize);
	void position(uint32 npos);			//返回npos的位置指针
	uint32 position();					//返回最后位置指针
	uint32 lenth();						//返回m_Buff的长度大小
	void erase();						//清除数据


private:
	std::vector<uint8> m_Buff;
	std::vector<uint8>::iterator m_Pointer;
};


#endif