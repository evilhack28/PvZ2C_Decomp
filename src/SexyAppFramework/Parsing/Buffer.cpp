//
//  Buffer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/Buffer.h"

using namespace Sexy;

/////////////// Reading ///////////////

int8 Buffer::ReadInt8() const
{
	return ReadByte();
}

bool Buffer::AtEnd() const
{
	return mReadBitPos >= mDataBitSize;
}

void Buffer::Clear()
{
	mReadBitPos = 0;
	mWriteBitPos = 0;
	mDataBitSize = 0;
	mData.clear();
}

int Buffer::GetDataLen() const
{
	return (mDataBitSize + 7) / 8;
}

short Buffer::ReadShort() const
{
	short aShort = ReadByte();
	aShort |= ReadByte() << 8;
	return aShort;
}
