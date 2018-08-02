#include "base_stream.h"

CStream::CStream(uint32 nSize)
{
	m_Buff.reserve(nSize);
	m_Pointer = m_Buff.begin();
}

CStream::~CStream()
{
	m_Buff.clear();
}

uint8& CStream::operator[](uint32 nindex)
{
	if (nindex > 1024)
	{
		//Խ��
		return m_Buff[0];
	}
	return m_Buff[nindex];
}
uint32 CStream::position()
{
	return (m_Buff.end() - m_Buff.begin());
}

uint32 CStream::lenth()
{
	return (uint32)(m_Buff.size());
}

void CStream::erase()
{
	m_Buff.erase(m_Buff.begin(), m_Pointer);
	m_Pointer = m_Buff.begin();
}

uint32 CStream::write(void* src, uint32 nsize)
{
	uint32 ncur = position();
	m_Buff.resize(ncur+nsize);
	memcpy(&m_Buff[ncur],src,nsize);
	return position();
}

uint32 CStream::read(void* buff,uint32 nsize)
{
	uint32 nPos = m_Pointer - m_Buff.begin();
	memcpy(buff, &m_Buff[nPos], nsize);
	position(nsize);
	return nsize;
}

void CStream::position(uint32 npos)
{
	m_Pointer = m_Buff.begin()+npos;
}