//
//  RtSerialRtonWriter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtSerial.h"

using namespace Sexy;

/////////////// Integers ///////////////

void RtSerialRtonWriter::WriteInt32(const RtSerialRtonKey& inKey, int32 inX)
{
	WriteKey(inKey);
	if (inX == 0)
	{
		WriteTag(RtSerialRtonTag::Int32Zero);
		return;
	}
	uint32 aUnsignedBytes = 0;
	for (uint32 v = inX; ; )
	{
		v >>= 7;
		aUnsignedBytes++;
		if (v == 0)
			break;
	}
	uint32 aSignedBytes = 0;
	for (uint32 v = (inX << 1) ^ (inX >> 31); ; )
	{
		v >>= 7;
		aSignedBytes++;
		if (v == 0)
			break;
	}
	if (aUnsignedBytes < 4)
	{
		if (aUnsignedBytes <= aSignedBytes)
		{
			WriteTag(RtSerialRtonTag::Int32VarU);
			mBuffer->WriteInt32VarU(inX);
			return;
		}
	}
	else if (aSignedBytes > 3)
	{
		WriteTag(RtSerialRtonTag::Int32Fixed);
		mBuffer->WriteInt32Fixed(inX);
		return;
	}
	WriteTag(RtSerialRtonTag::Int32VarS);
	mBuffer->WriteInt32VarS(inX);
}

void RtSerialRtonWriter::WriteUInt32(const RtSerialRtonKey& inKey, uint32 inX)
{
	WriteKey(inKey);
	if (inX == 0)
	{
		WriteTag(RtSerialRtonTag::UInt32Zero);
		return;
	}
	uint32 aBytes = 0;
	for (uint32 v = inX; ; )
	{
		v >>= 7;
		aBytes++;
		if (v == 0)
			break;
	}
	if (aBytes >= 4)
	{
		WriteTag(RtSerialRtonTag::UInt32Fixed);
		mBuffer->WriteUInt32Fixed(inX);
		return;
	}
	WriteTag(RtSerialRtonTag::UInt32VarU);
	mBuffer->WriteUInt32VarU(inX);
}

void RtSerialRtonWriter::WriteInt64(const RtSerialRtonKey& inKey, int64 inX)
{
	WriteKey(inKey);
	if (inX == 0)
	{
		WriteTag(RtSerialRtonTag::Int64Zero);
		return;
	}
	uint64 aUnsignedBytes = 0;
	for (uint64 v = inX; ; )
	{
		v >>= 7;
		aUnsignedBytes++;
		if (v == 0)
			break;
	}
	uint64 aSignedBytes = 0;
	for (uint64 v = (inX << 1) ^ (inX >> 63); ; )
	{
		v >>= 7;
		aSignedBytes++;
		if (v == 0)
			break;
	}
	if (aUnsignedBytes < 8)
	{
		if (aUnsignedBytes <= aSignedBytes)
		{
			WriteTag(RtSerialRtonTag::Int64VarU);
			mBuffer->WriteInt64VarU(inX);
			return;
		}
	}
	else if (aSignedBytes > 7)
	{
		WriteTag(RtSerialRtonTag::Int64Fixed);
		mBuffer->WriteInt64Fixed(inX);
		return;
	}
	WriteTag(RtSerialRtonTag::Int64VarS);
	mBuffer->WriteInt64VarS(inX);
}

void RtSerialRtonWriter::WriteUInt64(const RtSerialRtonKey& inKey, uint64 inX)
{
	WriteKey(inKey);
	if (inX == 0)
	{
		WriteTag(RtSerialRtonTag::UInt64Zero);
		return;
	}
	uint64 aBytes = 0;
	for (uint64 v = inX; ; )
	{
		v >>= 7;
		aBytes++;
		if (v == 0)
			break;
	}
	if (aBytes >= 8)
	{
		WriteTag(RtSerialRtonTag::UInt64Fixed);
		mBuffer->WriteUInt64Fixed(inX);
		return;
	}
	WriteTag(RtSerialRtonTag::UInt64VarU);
	mBuffer->WriteUInt64VarU(inX);
}

/////////////// Strings ///////////////

void RtSerialRtonWriter::WriteString(const RtSerialRtonKey& inKey, const std::string& inStr, bool inTracked)
{
	WriteKey(inKey);
	if (inTracked)
	{
		WriteTrackedString(inStr);
		return;
	}
	WriteTag(RtSerialRtonTag::AnsiString);
	mBuffer->WriteString(inStr);
}

void RtSerialRtonWriter::WriteString(const RtSerialRtonKey& inKey, const char* inStr, bool inTracked)
{
	WriteKey(inKey);
	if (inTracked)
		WriteTrackedString(inStr);
	else
	{
		WriteTag(RtSerialRtonTag::AnsiString);
		mBuffer->WriteString(inStr);
	}
}

void RtSerialRtonWriter::WriteUTF8String(const RtSerialRtonKey& inKey, const std::wstring& inStr, bool inTracked)
{
	WriteKey(inKey);
	if (inTracked)
	{
		WriteTrackedUTF8String(inStr);
		return;
	}
	WriteTag(RtSerialRtonTag::UTF8String);
	mBuffer->WriteUTF8String(inStr);
}

void RtSerialRtonWriter::WriteUTF8String(const RtSerialRtonKey& inKey, const wchar_t* inStr, bool inTracked)
{
	WriteKey(inKey);
	if (inTracked)
		WriteTrackedUTF8String(inStr);
	else
	{
		WriteTag(RtSerialRtonTag::UTF8String);
		mBuffer->WriteUTF8String(inStr);
	}
}

/////////////// RtId ///////////////

void RtSerialRtonWriter::WriteRtId(const RtSerialRtonKey& inKey, const RtId& inId)
{
	WriteKey(inKey);
	if (inId)
	{
		WriteTag(RtSerialRtonTag::RtId);
		RtId aId(inId);
		aId.Serialize(mBuffer);
	}
	else
		WriteTag(RtSerialRtonTag::RtIdNull);
}

void RtSerialRtonWriter::WriteRtId(const RtSerialRtonKey& inKey, const RtId::OfflineId& inOfflineId)
{
	WriteKey(inKey);
	if (inOfflineId)
	{
		WriteTag(RtSerialRtonTag::RtId);
		RtId::OfflineId anOfflineId(inOfflineId);
		anOfflineId.Serialize(mBuffer);
	}
	else
		WriteTag(RtSerialRtonTag::RtIdNull);
}

/////////////// Tracked strings ///////////////

void RtSerialRtonWriter::WriteTrackedString(const std::string& inStr)
{
	DTrackedAnsiStringMap::iterator anIt = mTrackedAnsiStringMap.find(inStr);
	if (anIt != mTrackedAnsiStringMap.end())
	{
		WriteTag(RtSerialRtonTag::TrackedAnsiStringExisting);
		mBuffer->WriteInt32VarU(anIt->second);
	}
	else
	{
		WriteTag(RtSerialRtonTag::TrackedAnsiStringNew);
		mBuffer->WriteString(inStr);
		mTrackedAnsiStringMap[inStr] = mTrackedAnsiStringCount++;
	}
}

void RtSerialRtonWriter::WriteTrackedUTF8String(const std::wstring& inStr)
{
	DTrackedUTF8StringMap::iterator anIt = mTrackedUTF8StringMap.find(inStr);
	if (anIt != mTrackedUTF8StringMap.end())
	{
		WriteTag(RtSerialRtonTag::TrackedUTF8StringExisting);
		mBuffer->WriteInt32VarU(anIt->second);
	}
	else
	{
		WriteTag(RtSerialRtonTag::TrackedUTF8StringNew);
		mBuffer->WriteUTF8String(inStr);
		mTrackedUTF8StringMap[inStr] = mTrackedUTF8StringCount++;
	}
}
