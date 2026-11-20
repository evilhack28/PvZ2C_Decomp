//
//  CBuffer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "logServer/buffer.h"

#include <cstdio>

/////////////// Lifecycle ///////////////

CBuffer::CBuffer(unsigned int size)
{
	m_buff = nullptr;
	m_size = 0;
	m_write = 0;
	m_read = 0;
	if (IsPowerOf2(size))
	{
		m_buff = new char[size];
		m_size = size;
		m_write = m_read = 0;
	}
	else
	{
		printf("error");
	}
}

CBuffer::~CBuffer()
{
	delete[] m_buff;
}

/////////////// Reading ///////////////

unsigned int CBuffer::Peek(char* buff, unsigned int len)
{
	unsigned int length = m_write - m_read;
	if (length == 0)
		return 0;

	unsigned int l = min(len, length);
	unsigned int off = m_read & (m_size - 1);
	unsigned int first = min(l, m_size - off);
	memcpy(buff, m_buff + off, first);
	memcpy(buff + first, m_buff, l - first);
	return l;
}

bool CBuffer::SeekReadPtr(unsigned int len)
{
	if (len > Length())
		return false;

	m_read += len;
	return true;
}

unsigned int CBuffer::Fetch(char* buff, unsigned int len)
{
	unsigned int length = m_write - m_read;
	if (length == 0)
		return 0;

	unsigned int l = min(len, length);
	unsigned int off = m_read & (m_size - 1);
	unsigned int first = min(l, m_size - off);
	memcpy(buff, m_buff + off, first);
	memcpy(buff + first, m_buff, l - first);
	m_read += l;
	return l;
}

unsigned int CBuffer::FetchChunk(char* buff, unsigned int len)
{
	if (m_write - m_read < len)
		return 0;

	return Fetch(buff, len);
}

/////////////// Writing ///////////////

bool CBuffer::Push(const char* buff, unsigned int len)
{
	unsigned int space = Space();
	if (len > space)
		return false;

	unsigned int l = min(len, space);
	unsigned int off = m_write & (m_size - 1);
	unsigned int first = min(l, m_size - off);
	memcpy(m_buff + off, buff, first);
	memcpy(m_buff, buff + first, l - first);
	m_write += l;
	return true;
}
