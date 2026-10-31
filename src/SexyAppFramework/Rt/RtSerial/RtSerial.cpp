//
//  RtSerial.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtSerial.h"
#include "SexyAppFramework/RtSerialJsonParser.h"
#include "SexyAppFramework/AutoCrit.h"
#include "SexyAppFramework/CritSect.h"
#include "SexyAppFramework/RtId.h"

using namespace Sexy;

static CritSect sJsonCritSect;

namespace
{
class RtonToJsonConverter
{
public:
	RtSerialBuffer* mBuffer;
	std::vector<bool> mScopeStack;
	std::vector<std::string> mTrackedStrings;
	std::vector<std::wstring> mTrackedWStrings;
	bool mOutputNewLines;
	std::string mNewLine;

	RtonToJsonConverter(bool inOutputNewLines)
	: mBuffer(NULL)
	, mOutputNewLines(inOutputNewLines)
	{
		mNewLine = inOutputNewLines ? "\r\n" : "";
	}

	std::string MakeIndent(uint32 inDepth)
	{
		if (!mOutputNewLines)
			return "";

		std::string indent;
		for (uint32 i = 0; i < inDepth / 4; i++)
			indent += '\t';
		for (uint32 i = 0; i < inDepth % 4; i++)
			indent += ' ';
		return indent;
	}

	void EscapeString(std::string& outJson, const std::string& inString)
	{
		outJson += "\"";
		for (int i = 0; i < (int)inString.size(); i++)
		{
			uchar c = inString[i];
			switch (c)
			{
			case '\b': outJson += "\\b"; break;
			case '\t': outJson += "\\t"; break;
			case '\n': outJson += "\\n"; break;
			case '\f': outJson += "\\f"; break;
			case '\r': outJson += "\\r"; break;
			case '"': outJson += "\\\""; break;
			case '/': outJson += "\\/"; break;
			case '\\': outJson += "\\\\"; break;
			default:
				if (c < ' ' || c > '~')
					outJson += StrFormat("\\u%04x", c);
				else
					outJson += (char)c;
				break;
			}
		}
		outJson += "\"";
	}

	void EscapeWString(std::string& outJson, const std::wstring& inString)
	{
		outJson += "\"";
		for (int i = 0; i < (int)inString.size(); i++)
		{
			ushort c = inString[i];
			switch (c)
			{
			case '\b': outJson += "\\b"; break;
			case '\t': outJson += "\\t"; break;
			case '\n': outJson += "\\n"; break;
			case '\f': outJson += "\\f"; break;
			case '\r': outJson += "\\r"; break;
			case '"': outJson += "\\\""; break;
			case '/': outJson += "\\/"; break;
			case '\\': outJson += "\\\\"; break;
			default:
				if (c < ' ' || c > '~')
					outJson += StrFormat("\\u%04x", c);
				else
					outJson += (char)c;
				break;
			}
		}
		outJson += "\"";
	}

	void ConvertMembers(std::string& outJson, uint32 inDepth)
	{
		std::string indent = MakeIndent(inDepth);
		if (mScopeStack.back())
		{
			uint8 tag = mBuffer->ReadInt8Fixed();
			while (tag != RtSerialRtonTag::MarkerArrayEnd)
			{
				outJson += StrFormat("%s%s", mNewLine.c_str(), indent.c_str());
				ConvertValue(tag, outJson, inDepth);
				tag = mBuffer->ReadInt8Fixed();
				if (tag == RtSerialRtonTag::MarkerArrayEnd)
					break;
				outJson += ",";
			}
		}
		else
		{
			uint8 tag = mBuffer->ReadInt8Fixed();
			while (tag != RtSerialRtonTag::MarkerObjectEnd)
			{
				outJson += StrFormat("%s%s", mNewLine.c_str(), indent.c_str());
				ConvertValue(tag, outJson, inDepth);
				outJson += ":";
				ConvertValue(mBuffer->ReadInt8Fixed(), outJson, inDepth);
				tag = mBuffer->ReadInt8Fixed();
				if (tag == RtSerialRtonTag::MarkerObjectEnd)
					break;
				outJson += ",";
			}
		}
	}

	void ConvertValue(uint32 inTag, std::string& outJson, uint32 inDepth)
	{
		switch (inTag)
		{
		case RtSerialRtonTag::BoolFalse:
			outJson += "false";
			break;
		case RtSerialRtonTag::BoolTrue:
			outJson += "true";
			break;
		case RtSerialRtonTag::AtomicThis:
			outJson += "\"*\"";
			break;
		case RtSerialRtonTag::Int8Fixed:
			outJson += StrFormat("%d", mBuffer->ReadInt8Fixed());
			break;
		case RtSerialRtonTag::Int8Zero:
		case RtSerialRtonTag::UInt8Zero:
		case RtSerialRtonTag::Int16Zero:
		case RtSerialRtonTag::UInt16Zero:
		case RtSerialRtonTag::Int32Zero:
		case RtSerialRtonTag::UInt32Zero:
		case RtSerialRtonTag::Int64Zero:
		case RtSerialRtonTag::UInt64Zero:
			outJson += "0";
			break;
		case RtSerialRtonTag::UInt8Fixed:
			outJson += StrFormat("%d", mBuffer->ReadUInt8Fixed());
			break;
		case RtSerialRtonTag::Int16Fixed:
			outJson += StrFormat("%d", mBuffer->ReadInt16Fixed());
			break;
		case RtSerialRtonTag::UInt16Fixed:
			outJson += StrFormat("%d", mBuffer->ReadUInt16Fixed());
			break;
		case RtSerialRtonTag::Int32Fixed:
			outJson += StrFormat("%d", mBuffer->ReadInt32Fixed());
			break;
		case RtSerialRtonTag::Float:
			outJson += StrFormat("%f", mBuffer->ReadFloat());
			break;
		case RtSerialRtonTag::FloatZero:
		case RtSerialRtonTag::DoubleZero:
			outJson += "0.0";
			break;
		case RtSerialRtonTag::Int32VarU:
			outJson += StrFormat("%d", mBuffer->ReadInt32VarU());
			break;
		case RtSerialRtonTag::Int32VarS:
			outJson += StrFormat("%d", mBuffer->ReadInt32VarS());
			break;
		case RtSerialRtonTag::UInt32Fixed:
			outJson += StrFormat("%d", mBuffer->ReadUInt32Fixed());
			break;
		case RtSerialRtonTag::UInt32VarU:
			outJson += StrFormat("%d", mBuffer->ReadUInt32VarU());
			break;
		case RtSerialRtonTag::Int64Fixed:
			outJson += StrFormat("%li", mBuffer->ReadInt64Fixed());
			break;
		case RtSerialRtonTag::Double:
			outJson += StrFormat("%f", mBuffer->ReadDouble());
			break;
		case RtSerialRtonTag::Int64VarU:
			outJson += StrFormat("%li", mBuffer->ReadInt64VarU());
			break;
		case RtSerialRtonTag::Int64VarS:
			outJson += StrFormat("%li", mBuffer->ReadInt64VarS());
			break;
		case RtSerialRtonTag::UInt64Fixed:
			outJson += StrFormat("%li", mBuffer->ReadUInt64Fixed());
			break;
		case RtSerialRtonTag::UInt64VarU:
			outJson += StrFormat("%li", mBuffer->ReadUInt64VarU());
			break;
		case RtSerialRtonTag::AnsiString:
		{
			std::string str;
			mBuffer->ReadString(str);
			EscapeString(outJson, str);
			break;
		}
		case RtSerialRtonTag::UTF8String:
		{
			std::wstring str;
			mBuffer->ReadUTF8String(str);
			EscapeWString(outJson, str);
			break;
		}
		case RtSerialRtonTag::RtId:
		{
			Sexy::RtId::OfflineId id;
			id.Serialize(mBuffer);
			std::string str;
			id.ToString(str);
			outJson += StrFormat("\"%s\"", str.c_str());
			break;
		}
		case RtSerialRtonTag::RtIdNull:
		{
			Sexy::RtId id;
			std::string str;
			id.ToString(str);
			outJson += StrFormat("\"%s\"", str.c_str());
			break;
		}
		case RtSerialRtonTag::Object:
		case RtSerialRtonTag::MemObject:
		{
			std::string indent = MakeIndent(inDepth);
			if (!mScopeStack.back())
				outJson += StrFormat("%s%s", mNewLine.c_str(), indent.c_str());
			outJson += "{";
			mScopeStack.push_back(false);
			ConvertMembers(outJson, inDepth + 4);
			mScopeStack.pop_back();
			outJson += StrFormat("%s%s}", mNewLine.c_str(), indent.c_str());
			break;
		}
		case RtSerialRtonTag::Array:
		case RtSerialRtonTag::MemArray:
		{
			std::string indent = MakeIndent(inDepth);
			if (inTag == RtSerialRtonTag::Array)
			{
				mBuffer->ReadInt8Fixed();
				mBuffer->ReadInt32VarU();
			}
			else
			{
				mBuffer->ReadInt8Fixed();
				int32 count = mBuffer->ReadInt32Fixed();
				mBuffer->SeekCurrent((count + 1) * 4);
			}
			if (!mScopeStack.back())
				outJson += StrFormat("%s%s", mNewLine.c_str(), indent.c_str());
			outJson += "[";
			mScopeStack.push_back(true);
			ConvertMembers(outJson, inDepth + 4);
			mScopeStack.pop_back();
			outJson += StrFormat("%s%s]", mNewLine.c_str(), indent.c_str());
			break;
		}
		case RtSerialRtonTag::BinaryBlob:
		{
			mBuffer->ReadInt8Fixed();
			std::string str;
			mBuffer->ReadString(str);
			int32 size = mBuffer->ReadInt32VarU();
			if (size)
				mBuffer->SeekCurrent(size);
			outJson += StrFormat("\"$BINARY(\"%s\", %d)\"", str.c_str(), size);
			break;
		}
		case RtSerialRtonTag::TrackedAnsiStringNew:
		{
			std::string str;
			mBuffer->ReadString(str);
			EscapeString(outJson, str);
			mTrackedStrings.push_back(str);
			break;
		}
		case RtSerialRtonTag::TrackedAnsiStringExisting:
		{
			int32 index = mBuffer->ReadInt32VarU();
			EscapeString(outJson, mTrackedStrings[index]);
			break;
		}
		case RtSerialRtonTag::TrackedUTF8StringNew:
		{
			std::wstring str;
			mBuffer->ReadUTF8String(str);
			EscapeWString(outJson, str);
			mTrackedWStrings.push_back(str);
			break;
		}
		case RtSerialRtonTag::TrackedUTF8StringExisting:
		{
			int32 index = mBuffer->ReadInt32VarU();
			EscapeWString(outJson, mTrackedWStrings[index]);
			break;
		}
		case RtSerialRtonTag::MemStringNew:
		{
			int32 size = mBuffer->ReadInt32Fixed();
			EscapeString(outJson, (const char*)(mBuffer->GetDataPtr() + mBuffer->Tell()));
			mBuffer->SeekCurrent(size);
			break;
		}
		case RtSerialRtonTag::MemStringExisting:
		{
			uint32 offset = mBuffer->ReadInt32Fixed();
			EscapeString(outJson, (const char*)(mBuffer->GetDataPtr() + offset));
			break;
		}
		case RtSerialRtonTag::MemWStringNew:
		{
			int32 size = mBuffer->ReadInt32Fixed();
			EscapeWString(outJson, (const wchar_t*)(mBuffer->GetDataPtr() + mBuffer->Tell()));
			mBuffer->SeekCurrent(size);
			break;
		}
		case RtSerialRtonTag::MemWStringExisting:
		{
			uint32 offset = mBuffer->ReadInt32Fixed();
			EscapeWString(outJson, (const wchar_t*)(mBuffer->GetDataPtr() + offset));
			break;
		}
		case RtSerialRtonTag::MemKeyStringNew:
		{
			int32 size = mBuffer->ReadInt32Fixed();
			EscapeString(outJson, (const char*)(mBuffer->GetDataPtr() + mBuffer->Tell()));
			mBuffer->SeekCurrent(size);
			mBuffer->ReadInt32Fixed();
			break;
		}
		case RtSerialRtonTag::MemKeyStringExisting:
		{
			uint32 offset = mBuffer->ReadInt32Fixed();
			EscapeString(outJson, (const char*)(mBuffer->GetDataPtr() + offset));
			mBuffer->ReadInt32Fixed();
			break;
		}
		case RtSerialRtonTag::MemKeyWStringNew:
		{
			int32 size = mBuffer->ReadInt32Fixed();
			EscapeWString(outJson, (const wchar_t*)(mBuffer->GetDataPtr() + mBuffer->Tell()));
			mBuffer->SeekCurrent(size);
			mBuffer->ReadInt32Fixed();
			break;
		}
		case RtSerialRtonTag::MemKeyWStringExisting:
		{
			uint32 offset = mBuffer->ReadInt32Fixed();
			EscapeWString(outJson, (const wchar_t*)(mBuffer->GetDataPtr() + offset));
			mBuffer->ReadInt32Fixed();
			break;
		}
		case RtSerialRtonTag::MemRtId:
		{
			Sexy::RtId id;
			id.Serialize(mBuffer);
			std::string str;
			id.ToString(str);
			outJson += StrFormat("\"%s\"", str.c_str());
			break;
		}
		case RtSerialRtonTag::MemBinaryBlob:
		{
			int8 type = mBuffer->ReadInt8Fixed();
			const char* str;
			if (type == (int8)RtSerialRtonTag::MemStringNew)
			{
				int32 size = mBuffer->ReadInt32Fixed();
				str = (const char*)(mBuffer->GetDataPtr() + mBuffer->Tell());
				mBuffer->SeekCurrent(size);
			}
			else if (type == (int8)RtSerialRtonTag::MemStringExisting)
			{
				uint32 offset = mBuffer->ReadInt32Fixed();
				str = (const char*)(mBuffer->GetDataPtr() + offset);
			}
			else
				str = "<unknown>";
			uint32 size = mBuffer->ReadInt32Fixed();
			if (size)
				mBuffer->SeekCurrent(size);
			outJson += StrFormat("\"$BINARY(\"%s\", %d)\"", str, size);
			break;
		}
		case RtSerialRtonTag::MemBool:
			outJson += mBuffer->ReadInt8Fixed() ? "true" : "false";
			break;
		}
	}
};
}

/////////////// Json ///////////////

bool RtSerial::RtonToJson(const uchar* inPtr, uint32 inSizeBytes, std::string& outJson, bool inShouldOutputNewLines)
{
	outJson = "";
	bool result = !inPtr || !inSizeBytes;
	if (result)
	{
		result = false;
	}
	else
	{
		RtSerialBuffer buffer((uchar*)inPtr, inSizeBytes);
		buffer.SetIsReading(true);
		if (__builtin_expect(buffer.ReadInt32Fixed() == RTSERIAL_RTON_MAGIC_BEGIN, 0) && __builtin_expect(buffer.ReadInt16Fixed() == 1, 1))
		{
			uint16 flags = buffer.ReadInt16Fixed();
			if (flags < 2 && (flags != 1 || buffer.ReadInt8Fixed() == (int8)RtSerialRtonTag::MemObject))
			{
				outJson += "{";
				RtonToJsonConverter converter(inShouldOutputNewLines);
				converter.mBuffer = &buffer;
				converter.mScopeStack.push_back(false);
				converter.ConvertMembers(outJson, 4);
				converter.mScopeStack.pop_back();
				if (__builtin_expect(buffer.ReadInt32Fixed() == RTSERIAL_RTON_MAGIC_END, 1))
				{
					result = true;
					std::string newLine = inShouldOutputNewLines ? "\r\n" : "";
					outJson += StrFormat("%s}%s", newLine.c_str(), newLine.c_str());
				}
			}
		}
	}
	return result;
}

bool RtSerial::JsonToRton(const char* inJson, RtSerialRtonWriter& outRton, std::string& outErrorString)
{
	AutoCrit crit(sJsonCritSect);
	static JsonParser sParser __attribute__((section(".bss.JsonParserInstance")));
	return sParser.ConvertToRton(inJson, outRton, outErrorString);
}

__asm__(".pushsection .bss.DsoHandle,\"aw\",@nobits\n.local __dso_handle\n__dso_handle: .zero 8\n.popsection");
