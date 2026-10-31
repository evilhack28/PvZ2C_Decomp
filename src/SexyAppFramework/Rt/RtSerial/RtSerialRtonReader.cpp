//
//  RtSerialRtonReader.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtSerial.h"

using namespace Sexy;

static const std::string sEmptyString;
static const std::wstring sEmptyWString;

/////////////// Lifecycle ///////////////

RtSerialRtonReader::RtSerialRtonReader(uchar* inFixedData, uint32 inFixedDataSize)
: mDoDeleteBuffer(true)
, mRootNode(0)
{
	mDecodeBuffer = new RtSerialRtonDecodeBuffer();
	if (mDecodeBuffer->Build(inFixedData, inFixedDataSize))
		InitDecodeBuffer();
}

RtSerialRtonReader::RtSerialRtonReader(RtSerialBuffer* inBuffer)
: mDoDeleteBuffer(true)
, mRootNode(0)
{
	mDecodeBuffer = new RtSerialRtonDecodeBuffer();
	if (inBuffer && mDecodeBuffer->Build(inBuffer->GetDataPtr(), inBuffer->GetDataSize()))
		InitDecodeBuffer();
}

RtSerialRtonReader::RtSerialRtonReader(RtSerialRtonDecodeBuffer* inDecodeBuffer)
: mDecodeBuffer(inDecodeBuffer)
, mDoDeleteBuffer(false)
, mRootNode(0)
{
	InitDecodeBuffer();
}

RtSerialRtonReader::~RtSerialRtonReader()
{
	if (mDoDeleteBuffer && mDecodeBuffer)
		delete mDecodeBuffer;
}

/////////////// Decode buffer ///////////////

bool RtSerialRtonReader::InitDecodeBuffer()
{
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(0);
	buffer->SetIsReading(true);
	bool ok = false;
	if (buffer->ReadInt32Fixed() == 0x4e4f5452)
	{
		if (buffer->ReadInt16Fixed() == 1)
		{
			int16 minor = buffer->ReadInt16Fixed();
			ok = minor == 1;
			if (ok)
				mRootNode = buffer->Tell();
		}
	}
	return ok;
}

RtSerialRtonTag::ETag RtSerialRtonReader::PeekTag()
{
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	return (RtSerialRtonTag::ETag)buffer->GetDataPtr()[buffer->Tell()];
}

RtSerialRtonTag::ETag RtSerialRtonReader::GetValueTag(HValue inValue)
{
	if (!inValue)
		return RtSerialRtonTag::MarkerObjectEnd;
	mDecodeBuffer->mBuffer.SeekStart(inValue);
	return PeekTag();
}

/////////////// Keys and containers ///////////////

const char* RtSerialRtonReader::GetKeyName(HKey inKey)
{
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(inKey);
	uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
	{
	case RtSerialRtonTag::MemKeyStringNew:
	case RtSerialRtonTag::MemKeyWStringNew:
		buffer->ReadInt32Fixed();
		return (const char*)buffer->GetDataPtr() + buffer->Tell();
	case RtSerialRtonTag::MemKeyStringExisting:
	case RtSerialRtonTag::MemKeyWStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		return (const char*)buffer->GetDataPtr() + offset;
	}
	}
	return NULL;
}

RtSerialRtonReader::HValue RtSerialRtonReader::GetKeyValue(HKey inKey)
{
	if (inKey)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inKey);
		uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
		{
		case RtSerialRtonTag::MemKeyStringNew:
		case RtSerialRtonTag::MemKeyWStringNew:
			buffer->SeekCurrent(buffer->ReadInt32Fixed());
			buffer->ReadInt32Fixed();
			return buffer->Tell();
		case RtSerialRtonTag::MemKeyStringExisting:
		case RtSerialRtonTag::MemKeyWStringExisting:
			buffer->ReadInt32Fixed();
			buffer->ReadInt32Fixed();
			return buffer->Tell();
		}
	}
	return 0;
}

bool RtSerialRtonReader::GetValueIsObject(HValue inValue)
{
	return GetValueTag(inValue) == RtSerialRtonTag::MemObject;
}

bool RtSerialRtonReader::GetValueIsArray(HValue inValue)
{
	return GetValueTag(inValue) == RtSerialRtonTag::MemArray;
}

RtSerialRtonReader::HKey RtSerialRtonReader::GetFirstChild(HValue inObject)
{
	if (inObject)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inObject);
		if (buffer->ReadInt8Fixed() == (int8)RtSerialRtonTag::MemObject && PeekTag() != RtSerialRtonTag::MarkerObjectEnd)
			return buffer->Tell();
	}
	return 0;
}

RtSerialRtonReader::HKey RtSerialRtonReader::GetNextSibling(HKey inKey)
{
	if (!inKey)
		return 0;
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(inKey);
	uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
	{
	case RtSerialRtonTag::MemKeyStringNew:
	case RtSerialRtonTag::MemKeyWStringNew:
		buffer->SeekCurrent(buffer->ReadInt32Fixed());
		buffer->SeekStart(buffer->ReadInt32Fixed());
		break;
	case RtSerialRtonTag::MemKeyStringExisting:
	case RtSerialRtonTag::MemKeyWStringExisting:
		buffer->ReadInt32Fixed();
		buffer->SeekStart(buffer->ReadInt32Fixed());
		break;
	}
	if (PeekTag() == RtSerialRtonTag::MarkerObjectEnd)
		return 0;
	return buffer->Tell();
}

uint32 RtSerialRtonReader::GetArrayCount(HValue inArray)
{
	if (inArray)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inArray);
		if (buffer->ReadInt8Fixed() == (int8)RtSerialRtonTag::MemArray)
		{
			buffer->ReadInt8Fixed();
			return buffer->ReadInt32Fixed();
		}
	}
	return 0;
}

RtSerialRtonReader::HKey RtSerialRtonReader::GetChildNamed(HValue inObject, const std::string& inName)
{
	if (inObject)
	{
		RtSerialRtonDecodeBuffer::DMemStringMap::iterator nameIt = mDecodeBuffer->mMemStringMap.find(inName);
		if (nameIt != mDecodeBuffer->mMemStringMap.end())
		{
			RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
			buffer->SeekStart(inObject);
			if (buffer->ReadInt8Fixed() == (int8)RtSerialRtonTag::MemObject)
			{
				HKey key = buffer->Tell();
				int8 tag = buffer->ReadInt8Fixed();
				while (tag != (int8)RtSerialRtonTag::MarkerObjectEnd)
				{
					switch (tag)
					{
					case (int8)RtSerialRtonTag::MemKeyStringNew:
					case (int8)RtSerialRtonTag::MemKeyWStringNew:
					{
						int32 skip = buffer->ReadInt32Fixed();
						if (nameIt->second == buffer->Tell())
							return key;
						buffer->SeekCurrent(skip);
						break;
					}
					case (int8)RtSerialRtonTag::MemKeyStringExisting:
					case (int8)RtSerialRtonTag::MemKeyWStringExisting:
						if (buffer->ReadInt32Fixed() == nameIt->second)
							return key;
						break;
					default:
						goto nextKey;
					}
					buffer->SeekStart(buffer->ReadInt32Fixed());
				nextKey:
					key = buffer->Tell();
					tag = buffer->ReadInt8Fixed();
				}
			}
		}
	}
	return 0;
}

RtSerialRtonReader::HValue RtSerialRtonReader::GetArrayIndexValue(HValue inArray, uint32 inIndex)
{
	if (inArray)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inArray);
		if (buffer->ReadInt8Fixed() == (int8)RtSerialRtonTag::MemArray)
		{
			buffer->ReadInt8Fixed();
			if (inIndex < buffer->ReadInt32Fixed())
			{
				buffer->SeekCurrent(inIndex << 2);
				return buffer->ReadInt32Fixed();
			}
		}
	}
	return 0;
}

/////////////// Leaf values ///////////////

bool RtSerialRtonReader::GetBool(HValue inValue, bool inDefaultValue)
{
	if (!inValue)
		return inDefaultValue;
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(inValue);
	uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
	{
	case RtSerialRtonTag::Int8Fixed:
		return buffer->ReadInt8Fixed() != 0;
	case RtSerialRtonTag::MemBool:
		return buffer->ReadInt8Fixed() != 0;
	case RtSerialRtonTag::UInt8Fixed:
		return buffer->ReadUInt8Fixed() != 0;
	case RtSerialRtonTag::Int16Fixed:
		return buffer->ReadInt16Fixed() != 0;
	case RtSerialRtonTag::UInt16Fixed:
		return buffer->ReadUInt16Fixed() != 0;
	case RtSerialRtonTag::Int32Fixed:
		return buffer->ReadInt32Fixed() != 0;
	case RtSerialRtonTag::UInt32Fixed:
		return buffer->ReadUInt32Fixed() != 0;
	case RtSerialRtonTag::Float:
		return buffer->ReadFloat() != 0.f;
	case RtSerialRtonTag::Int64Fixed:
		return buffer->ReadInt64Fixed() != 0;
	case RtSerialRtonTag::UInt64Fixed:
		return buffer->ReadUInt64Fixed() != 0;
	case RtSerialRtonTag::Double:
		return buffer->ReadDouble() != 0.0;
	case RtSerialRtonTag::MemStringNew:
	{
		buffer->ReadInt32Fixed();
		const char* str = (const char*)buffer->GetDataPtr() + buffer->Tell();
		return str[0] != 0 && str[0] != '0';
	}
	case RtSerialRtonTag::MemStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		const char* str = (const char*)buffer->GetDataPtr() + offset;
		return str[0] != 0 && str[0] != '0';
	}
	case RtSerialRtonTag::MemWStringNew:
	{
		buffer->ReadInt32Fixed();
		const wchar_t* str = (const wchar_t*)(buffer->GetDataPtr() + buffer->Tell());
		return str[0] != 0 && str[0] != L'0';
	}
	case RtSerialRtonTag::MemWStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		const wchar_t* str = (const wchar_t*)(buffer->GetDataPtr() + offset);
		return str[0] != 0 && str[0] != L'0';
	}
	case RtSerialRtonTag::MemRtId:
	{
		RtId id;
		id.Serialize(buffer);
		return id;
	}
	}
	return inDefaultValue;
}

int32 RtSerialRtonReader::GetInt32(HValue inValue, int32 inDefaultValue)
{
	if (!inValue)
		return inDefaultValue;
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(inValue);
	uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
	{
	case RtSerialRtonTag::Int8Fixed:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::MemBool:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::UInt8Fixed:
		return buffer->ReadUInt8Fixed();
	case RtSerialRtonTag::Int16Fixed:
		return buffer->ReadInt16Fixed();
	case RtSerialRtonTag::UInt16Fixed:
		return buffer->ReadUInt16Fixed();
	case RtSerialRtonTag::Int32Fixed:
		return buffer->ReadInt32Fixed();
	case RtSerialRtonTag::UInt32Fixed:
		return buffer->ReadUInt32Fixed();
	case RtSerialRtonTag::Float:
		return (int32)buffer->ReadFloat();
	case RtSerialRtonTag::Int64Fixed:
		return buffer->ReadInt64Fixed();
	case RtSerialRtonTag::UInt64Fixed:
		return buffer->ReadUInt64Fixed();
	case RtSerialRtonTag::Double:
		return (int32)buffer->ReadDouble();
	case RtSerialRtonTag::MemStringNew:
		buffer->ReadInt32Fixed();
		return atoi((const char*)buffer->GetDataPtr() + buffer->Tell());
	case RtSerialRtonTag::MemStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		return atoi((const char*)buffer->GetDataPtr() + offset);
	}
	case RtSerialRtonTag::MemWStringNew:
		buffer->ReadInt32Fixed();
		return _wtoi((const wchar_t*)(buffer->GetDataPtr() + buffer->Tell()));
	case RtSerialRtonTag::MemWStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		return _wtoi((const wchar_t*)(buffer->GetDataPtr() + offset));
	}
	case RtSerialRtonTag::MemRtId:
	{
		RtId id;
		id.Serialize(buffer);
		return id.GetValue();
	}
	}
	return inDefaultValue;
}

uint32 RtSerialRtonReader::GetUInt32(HValue inValue, uint32 inDefaultValue)
{
	if (!inValue)
		return inDefaultValue;
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(inValue);
	uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
	{
	case RtSerialRtonTag::Int8Fixed:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::MemBool:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::UInt8Fixed:
		return buffer->ReadUInt8Fixed();
	case RtSerialRtonTag::Int16Fixed:
		return buffer->ReadInt16Fixed();
	case RtSerialRtonTag::UInt16Fixed:
		return buffer->ReadUInt16Fixed();
	case RtSerialRtonTag::Int32Fixed:
		return buffer->ReadInt32Fixed();
	case RtSerialRtonTag::UInt32Fixed:
		return buffer->ReadUInt32Fixed();
	case RtSerialRtonTag::Float:
		return buffer->ReadFloat();
	case RtSerialRtonTag::Int64Fixed:
		return buffer->ReadInt64Fixed();
	case RtSerialRtonTag::UInt64Fixed:
		return buffer->ReadUInt64Fixed();
	case RtSerialRtonTag::Double:
		return buffer->ReadDouble();
	case RtSerialRtonTag::MemStringNew:
		buffer->ReadInt32Fixed();
			return atoi((const char*)buffer->GetDataPtr() + buffer->Tell());
	case RtSerialRtonTag::MemStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		return atoi((const char*)buffer->GetDataPtr() + offset);
	}
	case RtSerialRtonTag::MemWStringNew:
		buffer->ReadInt32Fixed();
			return _wtoi((const wchar_t*)(buffer->GetDataPtr() + buffer->Tell()));
	case RtSerialRtonTag::MemWStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		return _wtoi((const wchar_t*)(buffer->GetDataPtr() + offset));
	}
	case RtSerialRtonTag::MemRtId:
	{
		RtId id;
		id.Serialize(buffer);
		return id.GetValue();
	}
	}
	return inDefaultValue;
}

int64 RtSerialRtonReader::GetInt64(HValue inValue, int64 inDefaultValue)
{
	if (!inValue)
		return inDefaultValue;
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(inValue);
	uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
	{
	case RtSerialRtonTag::Int8Fixed:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::MemBool:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::UInt8Fixed:
		return buffer->ReadUInt8Fixed();
	case RtSerialRtonTag::Int16Fixed:
		return buffer->ReadInt16Fixed();
	case RtSerialRtonTag::UInt16Fixed:
		return buffer->ReadUInt16Fixed();
	case RtSerialRtonTag::Int32Fixed:
		return buffer->ReadInt32Fixed();
	case RtSerialRtonTag::UInt32Fixed:
		return buffer->ReadUInt32Fixed();
	case RtSerialRtonTag::Float:
		return buffer->ReadFloat();
	case RtSerialRtonTag::Int64Fixed:
		return buffer->ReadInt64Fixed();
	case RtSerialRtonTag::UInt64Fixed:
		return buffer->ReadUInt64Fixed();
	case RtSerialRtonTag::Double:
		return buffer->ReadDouble();
	case RtSerialRtonTag::MemStringNew:
	{
		buffer->ReadInt32Fixed();
		const char* str = (const char*)buffer->GetDataPtr() + buffer->Tell();
		int64 value = 0;
		sscanf(str, "%lld", &value);
		return value;
	}
	case RtSerialRtonTag::MemStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		const char* str = (const char*)buffer->GetDataPtr() + offset;
		int64 value = 0;
		sscanf(str, "%lld", &value);
		return value;
	}
	case RtSerialRtonTag::MemWStringNew:
	{
		buffer->ReadInt32Fixed();
		const wchar_t* str = (const wchar_t*)(buffer->GetDataPtr() + buffer->Tell());
		int64 value = 0;
		swscanf(str, L"%lld", &value);
		return value;
	}
	case RtSerialRtonTag::MemWStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		const wchar_t* str = (const wchar_t*)(buffer->GetDataPtr() + offset);
		int64 value = 0;
		swscanf(str, L"%lld", &value);
		return value;
	}
	case RtSerialRtonTag::MemRtId:
	{
		RtId id;
		id.Serialize(buffer);
		return id.GetValue();
	}
	}
	return inDefaultValue;
}

uint64 RtSerialRtonReader::GetUInt64(HValue inValue, uint64 inDefaultValue)
{
	if (!inValue)
		return inDefaultValue;
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(inValue);
	uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
	{
	case RtSerialRtonTag::Int8Fixed:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::MemBool:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::UInt8Fixed:
		return buffer->ReadUInt8Fixed();
	case RtSerialRtonTag::Int16Fixed:
		return buffer->ReadInt16Fixed();
	case RtSerialRtonTag::UInt16Fixed:
		return buffer->ReadUInt16Fixed();
	case RtSerialRtonTag::Int32Fixed:
		return buffer->ReadInt32Fixed();
	case RtSerialRtonTag::UInt32Fixed:
		return buffer->ReadUInt32Fixed();
	case RtSerialRtonTag::Float:
		return buffer->ReadFloat();
	case RtSerialRtonTag::Int64Fixed:
		return buffer->ReadInt64Fixed();
	case RtSerialRtonTag::UInt64Fixed:
		return buffer->ReadUInt64Fixed();
	case RtSerialRtonTag::Double:
		return buffer->ReadDouble();
	case RtSerialRtonTag::MemStringNew:
	{
		buffer->ReadInt32Fixed();
		const char* str = (const char*)buffer->GetDataPtr() + buffer->Tell();
		uint64 value = 0;
		sscanf(str, "%llu", &value);
		return value;
	}
	case RtSerialRtonTag::MemStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		const char* str = (const char*)buffer->GetDataPtr() + offset;
		uint64 value = 0;
		sscanf(str, "%llu", &value);
		return value;
	}
	case RtSerialRtonTag::MemWStringNew:
	{
		buffer->ReadInt32Fixed();
		const wchar_t* str = (const wchar_t*)(buffer->GetDataPtr() + buffer->Tell());
		uint64 value = 0;
		swscanf(str, L"%llu", &value);
		return value;
	}
	case RtSerialRtonTag::MemWStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		const wchar_t* str = (const wchar_t*)(buffer->GetDataPtr() + offset);
		uint64 value = 0;
		swscanf(str, L"%llu", &value);
		return value;
	}
	case RtSerialRtonTag::MemRtId:
	{
		RtId id;
		id.Serialize(buffer);
		return id.GetValue();
	}
	}
	return inDefaultValue;
}

float RtSerialRtonReader::GetFloat(HValue inValue, float inDefaultValue)
{
	if (!inValue)
		return inDefaultValue;
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(inValue);
	uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
	{
	case RtSerialRtonTag::Int8Fixed:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::MemBool:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::UInt8Fixed:
		return buffer->ReadUInt8Fixed();
	case RtSerialRtonTag::Int16Fixed:
		return buffer->ReadInt16Fixed();
	case RtSerialRtonTag::UInt16Fixed:
		return buffer->ReadUInt16Fixed();
	case RtSerialRtonTag::Int32Fixed:
		return buffer->ReadInt32Fixed();
	case RtSerialRtonTag::UInt32Fixed:
		return buffer->ReadUInt32Fixed();
	case RtSerialRtonTag::Float:
		return buffer->ReadFloat();
	case RtSerialRtonTag::Int64Fixed:
		return buffer->ReadInt64Fixed();
	case RtSerialRtonTag::UInt64Fixed:
		return buffer->ReadUInt64Fixed();
	case RtSerialRtonTag::Double:
		return buffer->ReadDouble();
	case RtSerialRtonTag::MemStringNew:
		buffer->ReadInt32Fixed();
			return atof((const char*)buffer->GetDataPtr() + buffer->Tell());
	case RtSerialRtonTag::MemStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		return atof((const char*)buffer->GetDataPtr() + offset);
	}
	case RtSerialRtonTag::MemWStringNew:
		buffer->ReadInt32Fixed();
			return _wtof((const wchar_t*)(buffer->GetDataPtr() + buffer->Tell()));
	case RtSerialRtonTag::MemWStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		return _wtof((const wchar_t*)(buffer->GetDataPtr() + offset));
	}
	case RtSerialRtonTag::MemRtId:
	{
		RtId id;
		id.Serialize(buffer);
		return id.GetValue();
	}
	}
	return inDefaultValue;
}

double RtSerialRtonReader::GetDouble(HValue inValue, double inDefaultValue)
{
	if (!inValue)
		return inDefaultValue;
	RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
	buffer->SeekStart(inValue);
	uint8 tag = buffer->ReadInt8Fixed();
	switch (tag)
	{
	case RtSerialRtonTag::Int8Fixed:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::MemBool:
		return buffer->ReadInt8Fixed();
	case RtSerialRtonTag::UInt8Fixed:
		return buffer->ReadUInt8Fixed();
	case RtSerialRtonTag::Int16Fixed:
		return buffer->ReadInt16Fixed();
	case RtSerialRtonTag::UInt16Fixed:
		return buffer->ReadUInt16Fixed();
	case RtSerialRtonTag::Int32Fixed:
		return buffer->ReadInt32Fixed();
	case RtSerialRtonTag::UInt32Fixed:
		return buffer->ReadUInt32Fixed();
	case RtSerialRtonTag::Float:
		return buffer->ReadFloat();
	case RtSerialRtonTag::Int64Fixed:
		return buffer->ReadInt64Fixed();
	case RtSerialRtonTag::UInt64Fixed:
		return buffer->ReadUInt64Fixed();
	case RtSerialRtonTag::Double:
		return buffer->ReadDouble();
	case RtSerialRtonTag::MemStringNew:
		buffer->ReadInt32Fixed();
			return atof((const char*)buffer->GetDataPtr() + buffer->Tell());
	case RtSerialRtonTag::MemStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		return atof((const char*)buffer->GetDataPtr() + offset);
	}
	case RtSerialRtonTag::MemWStringNew:
		buffer->ReadInt32Fixed();
			return _wtof((const wchar_t*)(buffer->GetDataPtr() + buffer->Tell()));
	case RtSerialRtonTag::MemWStringExisting:
	{
		uint32 offset = buffer->ReadInt32Fixed();
		return _wtof((const wchar_t*)(buffer->GetDataPtr() + offset));
	}
	case RtSerialRtonTag::MemRtId:
	{
		RtId id;
		id.Serialize(buffer);
		return id.GetValue();
	}
	}
	return inDefaultValue;
}

const char* RtSerialRtonReader::GetStringDirect(HValue inValue)
{
	if (inValue)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inValue);
		uint8 tag = buffer->ReadInt8Fixed();
		switch (tag)
		{
		case RtSerialRtonTag::MemStringNew:
		{
			uint32 size = buffer->ReadInt32Fixed();
			if (size > 1)
				return (const char*)buffer->GetDataPtr() + buffer->Tell();
			return sEmptyString.c_str();
		}
		case RtSerialRtonTag::MemStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			return (const char*)buffer->GetDataPtr() + offset;
		}
		}
	}
	return NULL;
}

const wchar_t* RtSerialRtonReader::GetWStringDirect(HValue inValue)
{
	if (inValue)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inValue);
		uint8 tag = buffer->ReadInt8Fixed();
		switch (tag)
		{
		case RtSerialRtonTag::MemWStringNew:
		{
			uint32 size = buffer->ReadInt32Fixed();
			if (size > 1)
				return (const wchar_t*)(buffer->GetDataPtr() + buffer->Tell());
			return sEmptyWString.c_str();
		}
		case RtSerialRtonTag::MemWStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			return (const wchar_t*)(buffer->GetDataPtr() + offset);
		}
		}
	}
	return NULL;
}

bool RtSerialRtonReader::GetBinaryBlob(HValue inValue, RtSerialBuffer* outBuffer, std::string& outContentType)
{
	if (inValue)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inValue);
		if (buffer->ReadInt8Fixed() == (int8)RtSerialRtonTag::MemBinaryBlob)
		{
			const char* contentType;
			uint8 tag = buffer->ReadInt8Fixed();
			switch (tag)
			{
			case RtSerialRtonTag::MemStringNew:
			{
				int32 size = buffer->ReadInt32Fixed();
				contentType = (const char*)buffer->GetDataPtr() + buffer->Tell();
				buffer->SeekCurrent(size);
				break;
			}
			case RtSerialRtonTag::MemStringExisting:
			{
				uint32 offset = buffer->ReadInt32Fixed();
				contentType = (const char*)buffer->GetDataPtr() + offset;
				break;
			}
			default:
				contentType = "";
				break;
			}
			outContentType = contentType;
			uint32 dataSize = buffer->ReadInt32Fixed();
			if (outBuffer)
				*outBuffer = RtSerialBuffer(buffer->GetDataPtr() + buffer->Tell(), dataSize);
			return true;
		}
	}
	return false;
}

RtId RtSerialRtonReader::GetRtId(HValue inValue, const RtId& inDefaultValue)
{
	if (inValue)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inValue);
		uint8 tag = buffer->ReadInt8Fixed();
		switch (tag)
		{
		case RtSerialRtonTag::Int8Fixed:
		case RtSerialRtonTag::UInt8Fixed:
		case RtSerialRtonTag::Int16Fixed:
		case RtSerialRtonTag::UInt16Fixed:
		case RtSerialRtonTag::Int32Fixed:
		case RtSerialRtonTag::Float:
		case RtSerialRtonTag::UInt32Fixed:
		case RtSerialRtonTag::Double:
		case RtSerialRtonTag::MemBool:
			return RtId();
		case RtSerialRtonTag::UInt64Fixed:
			return RtId(buffer->ReadUInt64Fixed());
		case RtSerialRtonTag::Int64Fixed:
			return RtId(buffer->ReadInt64Fixed());
		case RtSerialRtonTag::MemStringNew:
		{
			buffer->ReadInt32Fixed();
			return RtId::StaticParse((const char*)buffer->GetDataPtr() + buffer->Tell());
		}
		case RtSerialRtonTag::MemStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			return RtId::StaticParse((const char*)buffer->GetDataPtr() + offset);
		}
		case RtSerialRtonTag::MemWStringNew:
		{
			buffer->ReadInt32Fixed();
			return RtId::StaticParse((const wchar_t*)(buffer->GetDataPtr() + buffer->Tell()));
		}
		case RtSerialRtonTag::MemWStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			return RtId::StaticParse((const wchar_t*)(buffer->GetDataPtr() + offset));
		}
		case RtSerialRtonTag::MemRtId:
		{
			RtId id;
			id.Serialize(buffer);
			return id;
		}
		case RtSerialRtonTag::Int8Zero:
		case RtSerialRtonTag::UInt8Zero:
		case RtSerialRtonTag::Int16Zero:
		case RtSerialRtonTag::UInt16Zero:
		case RtSerialRtonTag::Int32Zero:
		case RtSerialRtonTag::FloatZero:
		case RtSerialRtonTag::UInt32Zero:
			return RtId();
		}
	}
	return inDefaultValue;
}

std::string RtSerialRtonReader::GetString(HValue inValue, const std::string& inDefaultValue)
{
	if (inValue)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inValue);
		uint8 tag = buffer->ReadInt8Fixed();
		switch (tag)
		{
		case RtSerialRtonTag::Int8Fixed:
			return StrFormat("%d", buffer->ReadInt8Fixed());
		case RtSerialRtonTag::UInt8Fixed:
			return StrFormat("%d", buffer->ReadUInt8Fixed());
		case RtSerialRtonTag::Int16Fixed:
			return StrFormat("%d", buffer->ReadInt16Fixed());
		case RtSerialRtonTag::UInt16Fixed:
			return StrFormat("%d", buffer->ReadUInt16Fixed());
		case RtSerialRtonTag::Int32Fixed:
			return StrFormat("%d", buffer->ReadInt32Fixed());
		case RtSerialRtonTag::Float:
			return StrFormat("%f", buffer->ReadFloat());
		case RtSerialRtonTag::UInt32Fixed:
			return StrFormat("%d", buffer->ReadUInt32Fixed());
		case RtSerialRtonTag::Int64Fixed:
			return StrFormat("%li", buffer->ReadInt64Fixed());
		case RtSerialRtonTag::Double:
			return StrFormat("%f", buffer->ReadDouble());
		case RtSerialRtonTag::UInt64Fixed:
			return StrFormat("%li", buffer->ReadUInt64Fixed());
		case RtSerialRtonTag::MemStringNew:
		{
			uint32 size = buffer->ReadInt32Fixed();
			if (size < 2)
				return sEmptyString;
			return (const char*)buffer->GetDataPtr() + buffer->Tell();
		}
		case RtSerialRtonTag::MemStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			return (const char*)buffer->GetDataPtr() + offset;
		}
		case RtSerialRtonTag::MemWStringNew:
		{
			uint32 size = buffer->ReadInt32Fixed();
			if (size < 2)
				return sEmptyString;
			return WStringToUTF8String((const wchar_t*)(buffer->GetDataPtr() + buffer->Tell()));
		}
		case RtSerialRtonTag::MemWStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			return WStringToUTF8String((const wchar_t*)(buffer->GetDataPtr() + offset));
		}
		case RtSerialRtonTag::MemObject:
			return "<Object>";
		case RtSerialRtonTag::MemArray:
			return "<Array>";
		case RtSerialRtonTag::MemRtId:
		{
			RtId id;
			id.Serialize(buffer);
			std::string str;
			id.ToString(str, false);
			return str;
		}
		case RtSerialRtonTag::MemBinaryBlob:
			return "<BinaryBlob>";
		case RtSerialRtonTag::MemBool:
			return buffer->ReadInt8Fixed() ? "true" : "false";
		}
	}
	return inDefaultValue;
}

std::wstring RtSerialRtonReader::GetWString(HValue inValue, const std::wstring& inDefaultValue)
{
	if (inValue)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inValue);
		uint8 tag = buffer->ReadInt8Fixed();
		switch (tag)
		{
		case RtSerialRtonTag::Int8Fixed:
			return StrFormat(L"%d", buffer->ReadInt8Fixed());
		case RtSerialRtonTag::UInt8Fixed:
			return StrFormat(L"%d", buffer->ReadUInt8Fixed());
		case RtSerialRtonTag::Int16Fixed:
			return StrFormat(L"%d", buffer->ReadInt16Fixed());
		case RtSerialRtonTag::UInt16Fixed:
			return StrFormat(L"%d", buffer->ReadUInt16Fixed());
		case RtSerialRtonTag::Int32Fixed:
			return StrFormat(L"%d", buffer->ReadInt32Fixed());
		case RtSerialRtonTag::Float:
			return StrFormat(L"%f", buffer->ReadFloat());
		case RtSerialRtonTag::UInt32Fixed:
			return StrFormat(L"%d", buffer->ReadUInt32Fixed());
		case RtSerialRtonTag::Int64Fixed:
			return StrFormat(L"%li", buffer->ReadInt64Fixed());
		case RtSerialRtonTag::Double:
			return StrFormat(L"%f", buffer->ReadDouble());
		case RtSerialRtonTag::UInt64Fixed:
			return StrFormat(L"%li", buffer->ReadUInt64Fixed());
		case RtSerialRtonTag::MemStringNew:
		{
			uint32 size = buffer->ReadInt32Fixed();
			if (size < 2)
				return sEmptyWString;
			return UTF8StringToWString((const char*)buffer->GetDataPtr() + buffer->Tell());
		}
		case RtSerialRtonTag::MemStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			return UTF8StringToWString((const char*)buffer->GetDataPtr() + offset);
		}
		case RtSerialRtonTag::MemWStringNew:
		{
			uint32 size = buffer->ReadInt32Fixed();
			if (size < 2)
				return sEmptyWString;
			return (const wchar_t*)(buffer->GetDataPtr() + buffer->Tell());
		}
		case RtSerialRtonTag::MemWStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			return (const wchar_t*)(buffer->GetDataPtr() + offset);
		}
		case RtSerialRtonTag::MemObject:
			return L"<Object>";
		case RtSerialRtonTag::MemArray:
			return L"<Array>";
		case RtSerialRtonTag::MemRtId:
		{
			RtId id;
			id.Serialize(buffer);
			std::wstring str;
			id.ToString(str, false);
			return str;
		}
		case RtSerialRtonTag::MemBinaryBlob:
			return L"<BinaryBlob>";
		case RtSerialRtonTag::MemBool:
			return buffer->ReadInt8Fixed() ? L"true" : L"false";
		}
	}
	return inDefaultValue;
}

bool RtSerialRtonReader::GetInvokeVariant(HValue inValue, RtInvokeVariant& outVariant)
{
	if (inValue)
	{
		RtSerialBuffer* buffer = &mDecodeBuffer->mBuffer;
		buffer->SeekStart(inValue);
		uint8 tag = buffer->ReadInt8Fixed();
		switch (tag)
		{
		case RtSerialRtonTag::Int8Fixed:
			outVariant = RtInvokeVariant(buffer->ReadInt8Fixed());
			return true;
		case RtSerialRtonTag::UInt8Fixed:
			outVariant = RtInvokeVariant(buffer->ReadUInt8Fixed());
			return true;
		case RtSerialRtonTag::Int16Fixed:
			outVariant = RtInvokeVariant(buffer->ReadInt16Fixed());
			return true;
		case RtSerialRtonTag::UInt16Fixed:
			outVariant = RtInvokeVariant(buffer->ReadUInt16Fixed());
			return true;
		case RtSerialRtonTag::Int32Fixed:
			outVariant = RtInvokeVariant(buffer->ReadInt32Fixed());
			return true;
		case RtSerialRtonTag::Float:
			outVariant = RtInvokeVariant(buffer->ReadFloat());
			return true;
		case RtSerialRtonTag::UInt32Fixed:
			outVariant = RtInvokeVariant(buffer->ReadUInt32Fixed());
			return true;
		case RtSerialRtonTag::Int64Fixed:
			outVariant = RtInvokeVariant(buffer->ReadInt64Fixed());
			return true;
		case RtSerialRtonTag::Double:
			outVariant = RtInvokeVariant(buffer->ReadDouble());
			return true;
		case RtSerialRtonTag::UInt64Fixed:
			outVariant = RtInvokeVariant(buffer->ReadUInt64Fixed());
			return true;
		case RtSerialRtonTag::MemStringNew:
			buffer->ReadInt32Fixed();
			outVariant = RtInvokeVariant((const char*)buffer->GetDataPtr() + buffer->Tell());
			return true;
		case RtSerialRtonTag::MemStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			outVariant = RtInvokeVariant((const char*)buffer->GetDataPtr() + offset);
			return true;
		}
		case RtSerialRtonTag::MemWStringNew:
			buffer->ReadInt32Fixed();
			outVariant = RtInvokeVariant((const wchar_t*)(buffer->GetDataPtr() + buffer->Tell()));
			return true;
		case RtSerialRtonTag::MemWStringExisting:
		{
			uint32 offset = buffer->ReadInt32Fixed();
			outVariant = RtInvokeVariant((const wchar_t*)(buffer->GetDataPtr() + offset));
			return true;
		}
		case RtSerialRtonTag::MemRtId:
		{
			RtId id;
			id.Serialize(buffer);
			outVariant = RtInvokeVariant(id.GetValue());
			return true;
		}
		case RtSerialRtonTag::MemBool:
			outVariant = RtInvokeVariant(buffer->ReadInt8Fixed() != 0);
			return true;
		case RtSerialRtonTag::Int8Zero:
		case RtSerialRtonTag::UInt8Zero:
		case RtSerialRtonTag::Int16Zero:
		case RtSerialRtonTag::UInt16Zero:
		case RtSerialRtonTag::Int32Zero:
		case RtSerialRtonTag::FloatZero:
		case RtSerialRtonTag::UInt32Zero:
			outVariant = RtInvokeVariant((uint32)0);
			return false;
		}
	}
	outVariant = RtInvokeVariant((uint32)0);
	return false;
}
