//
//  DInputStream.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "DStream.h"

#include <cstdlib>
#include <cstring>

bool DInputStream::readBoolean()
{
	return readByte() != 0;
}

unsigned char DInputStream::readByte()
{
	if (pos + 1 > length)
		return 0;

	return pBuff[pos++];
}

int DInputStream::readInt()
{
	if (pos + 4 > length)
		return 0;

	unsigned int value = *(unsigned int*)(pBuff + pos);
	pos += 4;
	if (needToHost)
		value = D_SWAP32(value);
	return value;
}

short DInputStream::readShort()
{
	if (pos + 2 > length)
		return 0;

	short value = *(short*)(pBuff + pos);
	if (needToHost)
		value = D_SWAP16(value);
	pos += 2;
	return value;
}

float DInputStream::readFloat()
{
	if (pos + 4 > length)
		return 0.0f;

	unsigned int value = *(unsigned int*)(pBuff + pos);
	pos += 4;
	if (needToHost)
		value = D_SWAP32(value);
	return *(float*)&value;
}

long long DInputStream::readLongLong()
{
	if (pos + 8 > length)
		return 0;

	long long value = *(long long*)(pBuff + pos);
	pos += 8;
	if (needToHost)
		return __builtin_bswap64(value);
	return value;
}

bool DInputStream::seek(size_t offset)
{
	bool result = false;
	if (offset < length)
	{
		pos = offset;
		result = true;
	}
	return result;
}

size_t DInputStream::readBuffer(void* buff, size_t length)
{
	if (!buff)
		return 0;

	if (pos + length > this->length)
		length = this->length - pos;
	memcpy(buff, pBuff, length);
	pos += length;
	return length;
}

bool DInputStream::readFromBuffer(const unsigned char* buffer, size_t length)
{
	if (length == 0)
		return false;

	pBuff = new unsigned char[length];
	this->length = length;
	memcpy(pBuff, buffer, length);
	return true;
}

/////////////// Lifecycle ///////////////

DInputStream::~DInputStream()
{
	if (pBuff)
		free(pBuff);
}

double DInputStream::readDouble()
{
	if (pos + 8 > length)
		return 0.0;

	unsigned long long value = *(unsigned long long*)(pBuff + pos);
	pos += 8;
	if (needToHost)
		value = __builtin_bswap64(value);
	return *(double*)&value;
}
