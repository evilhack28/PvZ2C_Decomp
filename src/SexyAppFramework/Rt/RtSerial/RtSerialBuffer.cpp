//
//  RtSerialBuffer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "RtSerial.h"

using namespace Sexy;

/////////////// Core read/write ///////////////

bool RtSerialBuffer::InternalMaybeRead(void* inPtr, uint32 inSize)
{
	if (inSize > 0)
	{
		if (mFixedData)
		{
			if (mCurOffset + inSize > mFixedDataSize)
				return false;
			if (inPtr)
				memcpy(inPtr, mFixedData + mCurOffset, inSize);
		}
		else
		{
			if (mCurOffset + inSize > (uint32)mDynData.size())
				return false;
			if (inPtr)
				memcpy(inPtr, &mDynData[mCurOffset], inSize);
		}
		mCurOffset += inSize;
	}
	return true;
}

void RtSerialBuffer::InternalRead(void* inPtr, uint32 inSize)
{
	memcpy(inPtr, mFixedData ? mFixedData + mCurOffset : &mDynData[mCurOffset], inSize);
	mCurOffset += inSize;
}

bool RtSerialBuffer::InternalMaybeWrite(const void* inPtr, uint32 inSize)
{
	if (inSize > 0)
	{
		if (mWriteCalcSizeOnly)
		{
			mCurOffset += inSize;
			return mWriteCalcSizeOnly;
		}
		if (mFixedData)
		{
			if (mCurOffset + inSize > mFixedDataSize)
				return false;
			if (inPtr)
				memcpy(mFixedData + mCurOffset, inPtr, inSize);
		}
		else
		{
			if (mCurOffset + inSize > (uint32)mDynData.size())
				mDynData.resize(mCurOffset + inSize);
			if (inPtr)
				memcpy(&mDynData[mCurOffset], inPtr, inSize);
		}
		mCurOffset += inSize;
	}
	return true;
}

void RtSerialBuffer::InternalWrite(const void* inPtr, uint32 inSize)
{
	if (mWriteCalcSizeOnly)
	{
		mCurOffset += inSize;
		return;
	}
	uchar* aDest;
	if (mFixedData)
		aDest = mFixedData + mCurOffset;
	else
	{
		if (mCurOffset + inSize > (uint32)mDynData.size())
			mDynData.resize(mCurOffset + inSize);
		aDest = &mDynData[mCurOffset];
	}
	memcpy(aDest, inPtr, inSize);
	mCurOffset += inSize;
}

/////////////// Varints ///////////////

int32 RtSerialBuffer::ReadInt32VarU()
{
	uint32 x = 0;
	uint32 aShift = 0;
	uint8 aByte;
	do
	{
		aByte = ReadInt8Fixed();
		x |= (aByte & 0x7f) << aShift;
		aShift += 7;
	}
	while (aByte & 0x80);
	return x;
}

int64 RtSerialBuffer::ReadInt64VarU()
{
	uint64 x = 0;
	uint64 aShift = 0;
	uint8 aByte;
	do
	{
		aByte = ReadInt8Fixed();
		x |= (uint64)(aByte & 0x7f) << aShift;
		aShift += 7;
	}
	while (aByte & 0x80);
	return x;
}

int32 RtSerialBuffer::ReadInt32VarS()
{
	uint32 x = ReadInt32VarU();
	return (x >> 1) ^ -(x & 1);
}

int64 RtSerialBuffer::ReadInt64VarS()
{
	uint64 x = ReadInt64VarU();
	return (x >> 1) ^ -(x & 1);
}

void RtSerialBuffer::WriteInt32VarS(int32 inX)
{
	WriteInt32VarU((inX << 1) ^ (inX >> 31));
}

void RtSerialBuffer::WriteInt64VarS(int64 inX)
{
	WriteInt64VarU((inX << 1) ^ (inX >> 63));
}

void RtSerialBuffer::WriteInt32VarU(int32 inX)
{
	uint32 x = (uint32)inX;
	do
	{
		uint8 aByte = x & 0x7f;
		x >>= 7;
		if (x)
			aByte |= 0x80;
		WriteInt8Fixed(aByte);
	}
	while (x);
}

void RtSerialBuffer::WriteInt64VarU(int64 inX)
{
	uint64 x = (uint64)inX;
	do
	{
		uint8 aByte = x & 0x7f;
		x >>= 7;
		if (x)
			aByte |= 0x80;
		WriteInt8Fixed(aByte);
	}
	while (x);
}

/////////////// Strings ///////////////

void RtSerialBuffer::ReadString(std::string& outStr)
{
	uint32 aLen = ReadInt32VarU();
	if (aLen > 0)
	{
		outStr.resize(aLen, 0);
		Read((void*)outStr.data(), aLen);
	}
	else
		outStr.clear();
}

void RtSerialBuffer::ReadWString(std::wstring& outStr)
{
	uint32 aLen = ReadInt32VarU();
	if (aLen > 0)
	{
		outStr.resize(aLen, 0);
		Read((void*)outStr.data(), aLen * sizeof(wchar_t));
	}
	else
		outStr.clear();
}

void RtSerialBuffer::WriteString(const std::string& inStr)
{
	uint32 aLen = (uint32)inStr.length();
	WriteInt32VarU(aLen);
	if (aLen != 0)
		Write(inStr.c_str(), aLen);
}

void RtSerialBuffer::WriteWString(const std::wstring& inStr)
{
	uint32 aLen = (uint32)inStr.length();
	WriteInt32VarU(aLen);
	if (aLen != 0)
		Write(inStr.c_str(), aLen * sizeof(wchar_t));
}

void RtSerialBuffer::WriteString(const char* inStr)
{
	uint32 aLen = 0;
	if (inStr && *inStr)
		aLen = (uint32)strlen(inStr);
	WriteInt32VarU(aLen);
	if (aLen > 0)
		Write(inStr, aLen);
}

void RtSerialBuffer::WriteWString(const wchar_t* inStr)
{
	uint32 aLen = 0;
	if (inStr && *inStr)
		aLen = (uint32)wcslen(inStr);
	WriteInt32VarU(aLen);
	if (aLen > 0)
		Write(inStr, aLen * sizeof(wchar_t));
}

/////////////// UTF-8 ///////////////

void RtSerialBuffer::ReadUTF8String(std::wstring& outStr)
{
	uint32 aLen = ReadInt32VarU();
	ReadInt32VarU();
	outStr.clear();
	outStr.reserve(aLen);
	for (uint32 i = 0; i < aLen; i++)
		outStr.push_back(ReadUTF8Char());
}

wchar_t RtSerialBuffer::ReadUTF8Char()
{
	uint32 aLen = GetDataSize() - Tell();
	const char* aStart = (const char*)GetDataPtr() + Tell();
	const char* aPtr = aStart;
	wchar_t aChar;
	if (!GetNextUTF8CharFromStream(&aPtr, aLen, &aChar))
		return 0;
	SeekCurrent(aPtr - aStart);
	return aChar;
}

uint32 RtSerialBuffer::InternalGetUTF8EncodedLengthForChar(uint32 inChar)
{
	if (inChar < 0x80)
		return 1;
	if (inChar < 0x800)
		return 2;
	if (inChar < 0x10000)
		return 3;
	if (inChar <= 0x10ffff)
		return 4;
	return 0;
}

void RtSerialBuffer::WriteUTF8Char(uint32 inChar)
{
	if (inChar < 0x80)
	{
		WriteInt8Fixed(inChar);
	}
	else if (inChar < 0x800)
	{
		WriteInt8Fixed(0xc0 | (inChar >> 6));
		WriteInt8Fixed(0x80 | (inChar & 0x3f));
	}
	else if (inChar < 0x10000)
	{
		WriteInt8Fixed(0xe0 | (inChar >> 12));
		WriteInt8Fixed(0x80 | ((inChar >> 6) & 0x3f));
		WriteInt8Fixed(0x80 | (inChar & 0x3f));
	}
	else if (inChar <= 0x10ffff)
	{
		WriteInt8Fixed(0xf0 | (inChar >> 18));
		WriteInt8Fixed(0x80 | ((inChar >> 12) & 0x3f));
		WriteInt8Fixed(0x80 | ((inChar >> 6) & 0x3f));
		WriteInt8Fixed(0x80 | (inChar & 0x3f));
	}
}

void RtSerialBuffer::WriteUTF8String(const std::wstring& inStr)
{
	uint32 aLen = (uint32)inStr.length();
	WriteInt32VarU(aLen);
	if (aLen != 0)
	{
		uint32 aByteLen = 0;
		for (uint32 i = 0; i < aLen; i++)
			aByteLen += InternalGetUTF8EncodedLengthForChar(inStr[i]);
		WriteInt32VarU(aByteLen);
		for (uint32 i = 0; i < aLen; i++)
			WriteUTF8Char(inStr[i]);
	}
	else
		WriteInt32VarU(0);
}

void RtSerialBuffer::WriteUTF8String(const wchar_t* inStr)
{
	uint32 aLen = 0;
	if (inStr && *inStr)
		aLen = (uint32)wcslen(inStr);
	WriteInt32VarU(aLen);
	uint32 aByteLen = 0;
	for (uint32 i = 0; i < aLen; i++)
		aByteLen += InternalGetUTF8EncodedLengthForChar(inStr[i]);
	WriteInt32VarU(aByteLen);
	for (uint32 i = 0; i < aLen; i++)
		WriteUTF8Char(inStr[i]);
}
