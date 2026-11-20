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

Buffer::~Buffer()
{
}

short Buffer::ReadInt16() const
{
	short aShort = ReadByte();
	aShort |= ReadByte() << 8;
	return aShort;
}

uchar Buffer::ReadByte() const
{
	if ((mReadBitPos + 7) / 8 >= (int)mData.size())
		return 0;

	if ((mReadBitPos & 7) == 0)
	{
		uchar aByte = mData[mReadBitPos / 8];
		mReadBitPos += 8;
		return aByte;
	}

	int aBytePos = mReadBitPos / 8;
	int aBitPos = mReadBitPos % 8;
	uchar aByte = mData[aBytePos] >> aBitPos;
	aByte |= mData[aBytePos + 1] << (8 - aBitPos);
	mReadBitPos += 8;
	return aByte;
}

int Buffer::ReadInt() const
{
	int aInt = ReadByte();
	aInt |= ReadByte() << 8;
	aInt |= ReadByte() << 16;
	aInt |= ReadByte() << 24;
	return aInt;
}

int64 Buffer::ReadInt64() const
{
	int64 aLong = ReadByte();
	aLong |= (int64)ReadByte() << 8;
	aLong |= (int64)ReadByte() << 16;
	aLong |= (int64)ReadByte() << 24;
	aLong |= (int64)ReadByte() << 32;
	aLong |= (int64)ReadByte() << 40;
	aLong |= (int64)ReadByte() << 48;
	aLong |= (int64)ReadByte() << 56;
	return aLong;
}

void Buffer::ReadBytes(uchar* theData, int theCount) const
{
	for (int i = 0; i < theCount; i++)
		theData[i] = ReadByte();
}

void Buffer::ReadBuffer(ByteVector* theByteVector) const
{
	theByteVector->clear();
	int aLen = ReadInt32();
	if (aLen > 0)
	{
		theByteVector->resize(aLen);
		ReadBytes(theByteVector->data(), aLen);
	}
	else
		theByteVector->clear();
}

void Buffer::ReadBuffer(Buffer* theBuffer) const
{
	ReadBuffer(&theBuffer->mData);
	theBuffer->mWriteBitPos = theBuffer->mDataBitSize = theBuffer->mData.size() * 8;
}

std::string Buffer::ReadLine() const
{
	std::string aString;
	for (;;)
	{
		uchar aChar = ReadByte();
		if (aChar == 10)
			break;
		else if (aChar == 0)
			break;
		else if (aChar != 13)
			aString += aChar;
	}
	return aString;
}

std::wstring Buffer::UTF8ToWideString() const
{
	const char* aPtr = (const char*)GetDataPtr();
	int aLen = GetDataLen();
	std::wstring aString;
	aString.reserve(aLen);
	bool isFirst = true;
	while (aLen > 0)
	{
		wchar_t aChar;
		int aNumChars = GetNextUTF8CharFromStream(&aPtr, aLen, &aChar);
		if (aNumChars == 0)
			break;
		aLen -= aNumChars;
		if (!isFirst || aChar != 0xFEFF)
			aString += aChar;
		isFirst = false;
	}
	return aString;
}

uchar* Buffer::GetDataPtr()
{
	if (mData.size() > 0)
		return mData.data();
	return NULL;
}

const uchar* Buffer::GetDataPtr() const
{
	if (mData.size() > 0)
		return mData.data();
	return NULL;
}

/////////////// Writing ///////////////

void Buffer::WriteByte(uchar theByte)
{
	if ((mWriteBitPos & 7) == 0)
		mData.push_back((uchar)theByte);
	else
	{
		int aBytePos = mWriteBitPos / 8;
		int aBitPos = mWriteBitPos % 8;
		mData[aBytePos] |= theByte << aBitPos;
		mData.push_back(theByte >> (8 - aBitPos));
	}

	mWriteBitPos += 8;
	if (mWriteBitPos > mDataBitSize)
		mDataBitSize = mWriteBitPos;
}

void Buffer::WriteBytes(const uchar* theByte, size_t theCount)
{
	if ((mWriteBitPos & 7) == 0)
	{
		mData.insert(mData.end(), theByte, theByte + theCount);
		mWriteBitPos += (int)theCount * 8;
		if (mWriteBitPos > mDataBitSize)
			mDataBitSize = mWriteBitPos;
	}
	else
	{
		for (size_t i = 0; i < theCount; i++)
			WriteByte(theByte[i]);
	}
}

void Buffer::WriteLine(const std::string& theString)
{
	WriteBytes((const uchar*)(theString + "\r\n").c_str(), (int)theString.length() + 2);
}

void Buffer::SetData(const ByteVector& theBuffer)
{
	mData = theBuffer;
	mWriteBitPos = mDataBitSize = mData.size() * 8;
}

void Buffer::SetData(const uchar* thePtr, int theCount)
{
	mData.clear();
	mData.reserve(theCount);
	mData.insert(mData.begin(), thePtr, thePtr + theCount);
	mWriteBitPos = mDataBitSize = mData.size() * 8;
}

/////////////// Lifecycle ///////////////

Buffer::Buffer()
	: mDataBitSize(0)
	, mReadBitPos(0)
	, mWriteBitPos(0)
{
}

void Buffer::Reserve(uint32 bytes)
{
	if (bytes > (uint32)mData.size())
		mData.reserve(bytes);
}

void Buffer::Resize(uint32 bytes)
{
	Clear();
	mDataBitSize = bytes * 8;
	mData.resize(bytes);
}

void Buffer::ResizeNonDestructive(size_t bytes)
{
	mDataBitSize = bytes * 8;
	mReadBitPos = std::min(mReadBitPos, mDataBitSize);
	mWriteBitPos = std::min(mWriteBitPos, mDataBitSize);
	mData.resize(bytes);
}

/////////////// Reading (cont.) ///////////////

int Buffer::GetBitsAvailable() const
{
	if (AtEnd())
		return 0;
	return mDataBitSize - mReadBitPos;
}

int Buffer::GetBytesAvailable() const
{
	return GetBitsAvailable() / 8;
}

int32 Buffer::ReadInt32() const
{
	int32 aInt = ReadByte();
	aInt |= ReadByte() << 8;
	aInt |= ReadByte() << 16;
	aInt |= ReadByte() << 24;
	return aInt;
}

std::string Buffer::ReadString() const
{
	std::string aString;
	int aLen = ReadShort();
	for (int i = 0; i < aLen; i++)
		aString += ReadByte();
	return aString;
}

/////////////// Writing (cont.) ///////////////

void Buffer::WriteShort(short theShort)
{
	WriteByte(theShort);
	WriteByte(theShort >> 8);
}

void Buffer::WriteInt16(short theShort)
{
	WriteByte(theShort);
	WriteByte(theShort >> 8);
}

void Buffer::WriteInt64(int64 theLong)
{
	WriteByte(theLong);
	WriteByte(theLong >> 8);
	WriteByte(theLong >> 16);
	WriteByte(theLong >> 24);
	WriteByte(theLong >> 32);
	WriteByte(theLong >> 40);
	WriteByte(theLong >> 48);
	WriteByte(theLong >> 56);
}

void Buffer::WriteBuffer(const ByteVector& theBuffer)
{
	WriteInt32(theBuffer.size());
	for (int i = 0; i < (int)theBuffer.size(); i++)
		WriteByte(theBuffer[i]);
}

void Buffer::WriteString(const std::string& theString)
{
	WriteInt16(theString.length());
	for (int i = 0; i < (int)theString.length(); i++)
		WriteByte(theString[i]);
}

bool Buffer::ReadBoolean() const
{
	return ReadByte() != 0;
}

float Buffer::ReadFloat() const
{
	int aInt = ReadByte();
	aInt |= ReadByte() << 8;
	aInt |= ReadByte() << 16;
	aInt |= ReadByte() << 24;
	return *(float*)&aInt;
}

double Buffer::ReadDouble() const
{
	int64 aLong = ReadByte();
	aLong |= (int64)ReadByte() << 8;
	aLong |= (int64)ReadByte() << 16;
	aLong |= (int64)ReadByte() << 24;
	aLong |= (int64)ReadByte() << 32;
	aLong |= (int64)ReadByte() << 40;
	aLong |= (int64)ReadByte() << 48;
	aLong |= (int64)ReadByte() << 56;
	return *(double*)&aLong;
}

FPoint Buffer::ReadFPoint() const
{
	FPoint aPoint;
	aPoint.mX = ReadDouble();
	aPoint.mY = ReadDouble();
	return aPoint;
}

SexyString Buffer::ReadSexyString() const
{
	int aLen = ReadInt16();
	SexyString aString;
	for (int i = 0; i < aLen; i++)
	{
		wchar_t aChar;
		ReadBytes((uchar*)&aChar, 4);
		aString += aChar;
	}
	return aString;
}

void Buffer::SeekFront() const
{
	mReadBitPos = 0;
}

int Buffer::GetDataLenBits() const
{
	return mDataBitSize;
}

bool Buffer::PastEnd() const
{
	return mReadBitPos > mDataBitSize;
}

void Buffer::WriteBoolean(bool theBool)
{
	WriteByte(theBool);
}

void Buffer::WriteInt8(int8 theInt8)
{
	WriteByte(theInt8);
}

void Buffer::WriteInt(int theInt)
{
	WriteByte(theInt);
	WriteByte(theInt >> 8);
	WriteByte(theInt >> 16);
	WriteByte(theInt >> 24);
}

void Buffer::WriteInt32(int32 theInt32)
{
	WriteByte(theInt32);
	WriteByte(theInt32 >> 8);
	WriteByte(theInt32 >> 16);
	WriteByte(theInt32 >> 24);
}

void Buffer::WriteFloat(float theFloat)
{
	int aInt = *(int*)&theFloat;
	WriteByte(aInt);
	WriteByte(aInt >> 8);
	WriteByte(aInt >> 16);
	WriteByte(aInt >> 24);
}

void Buffer::WriteDouble(double theDouble)
{
	int64 aLong = *(int64*)&theDouble;
	WriteByte(aLong);
	WriteByte(aLong >> 8);
	WriteByte(aLong >> 16);
	WriteByte(aLong >> 24);
	WriteByte(aLong >> 32);
	WriteByte(aLong >> 40);
	WriteByte(aLong >> 48);
	WriteByte(aLong >> 56);
}

void Buffer::WriteFPoint(FPoint thePoint)
{
	WriteDouble(thePoint.mX);
	WriteDouble(thePoint.mY);
}

void Buffer::WriteSexyString(const SexyString& theString)
{
	WriteInt16(theString.length());
	WriteBytes((const uchar*)theString.c_str(), (int)theString.length() * 4L);
}

void Buffer::WriteBuffer(const Buffer& theBuffer)
{
	WriteBuffer(theBuffer.mData);
}

/////////////// Bits ///////////////

void Buffer::WriteNumBits(int theNum, int theBits)
{
	for (int aBitNum = 0; aBitNum < theBits; aBitNum++)
	{
		if ((mWriteBitPos & 7) == 0)
			mData.push_back(0);

		if ((theNum & (1 << aBitNum)) != 0)
			mData[mWriteBitPos / 8] |= (1 << (mWriteBitPos % 8));

		mWriteBitPos++;
	}

	if (mWriteBitPos > mDataBitSize)
		mDataBitSize = mWriteBitPos;
}

/////////////// Varints ///////////////

void Buffer::WriteBase128VarIntS32(int32 theInt32)
{
	WriteBase128VarIntU32((theInt32 << 1) ^ (theInt32 >> 31));
}

void Buffer::WriteBase128VarIntS64(int64 theInt64)
{
	WriteBase128VarIntU64((theInt64 << 1) ^ (theInt64 >> 63));
}

int32 Buffer::ReadBase128VarIntU32() const
{
	uint32 aValue = 0;
	int aShift = 0;
	int8 aByte;
	do
	{
		aByte = ReadInt8();
		aValue |= (aByte & 0x7f) << aShift;
		aShift += 7;
	}
	while (aByte < 0);
	return aValue;
}

int64 Buffer::ReadBase128VarIntU64() const
{
	uint64 aValue = 0;
	int64 aShift = 0;
	int8 aByte;
	do
	{
		aByte = ReadInt8();
		aValue |= (uint64)(aByte & 0x7f) << aShift;
		aShift += 7;
	}
	while (aByte < 0);
	return aValue;
}

int32 Buffer::ReadBase128VarIntS32() const
{
	uint32 aValue = ReadBase128VarIntU32();
	return (aValue >> 1) ^ -(int32)(aValue & 1);
}

int64 Buffer::ReadBase128VarIntS64() const
{
	uint64 aValue = ReadBase128VarIntU64();
	return (aValue >> 1) ^ -(int64)(aValue & 1);
}
