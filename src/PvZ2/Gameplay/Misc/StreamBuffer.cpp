//
//  StreamBuffer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "sock_buffer.h"

#include <sys/endian.h>

/////////////// Lifecycle ///////////////

StreamBuffer::StreamBuffer(unsigned int size) : CBuffer(size)
{
}

StreamBuffer::~StreamBuffer()
{
}

/////////////// Buffer access ///////////////

char* StreamBuffer::GetBufReadStart(unsigned int& len)
{
	unsigned int length = m_write - m_read;
	if (length != 0)
	{
		len = min(length, m_size - (m_read & (m_size - 1)));
		return m_buff + (m_read & (m_size - 1));
	}
	return 0;
}

void StreamBuffer::SetBuffReadPos(unsigned int posDelt)
{
	m_read += posDelt;
}

void StreamBuffer::Clean()
{
	m_read = 0;
	m_write = 0;
}

char* StreamBuffer::GetBufWriteStart(unsigned int& len)
{
	unsigned int space = m_size + m_read - m_write;
	if (space != 0)
	{
		len = min(space, m_size - (m_write & (m_size - 1)));
		return m_buff + (m_write & (m_size - 1));
	}
	return 0;
}

void StreamBuffer::SetBuffWrtieStart(unsigned int posDelt)
{
	m_write += posDelt;
}

/////////////// Packets ///////////////

int StreamBuffer::CheckGetAPackage(char* oBuff, unsigned short maxLen)
{
	unsigned short len = 0;
	if (Peek((char*)&len, 2) < 2)
		return -1;

	len = ntohs(len);
	if (len > maxLen)
		return -2;

	m_read += 2;
	int ret = FetchChunk(oBuff, len);
	if (ret == 0)
		m_read -= 2;
	return ret;
}

int StreamBuffer::CheckGetAPackage(char* oBuff, unsigned int maxLen)
{
	unsigned int len = 0;
	if (Peek((char*)&len, 4) < 4)
		return -1;

	len = ntohl(len);
	if (len > maxLen)
		return -2;

	m_read += 4;
	int ret = FetchChunk(oBuff, len);
	if (ret == 0)
		m_read -= 4;
	return ret;
}

bool StreamBuffer::PushAPacket(const char* iBuff, unsigned short masLen)
{
	unsigned short len = htons(masLen);
	bool ret = false;
	if (Push((const char*)&len, 2))
	{
		ret = true;
		if (!Push(iBuff, masLen))
		{
			ret = false;
			m_write -= 2;
		}
	}
	return ret;
}

bool StreamBuffer::PushAPacket(const char* iBuff, unsigned int msgLen)
{
	unsigned int len = htonl(msgLen);
	bool ret = false;
	if (Push((const char*)&len, 4))
	{
		ret = true;
		if (!Push(iBuff, msgLen))
		{
			ret = false;
			m_write -= 4;
		}
	}
	return ret;
}

bool StreamBuffer::PushAPakcetNoLen(const char* iBuff, unsigned short msgLen)
{
	return Push(iBuff, msgLen);
}
