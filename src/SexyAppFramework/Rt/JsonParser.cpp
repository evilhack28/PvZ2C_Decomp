//
//  JsonParser.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtSerialJsonParser.h"
#include "SexyAppFramework/Feast.h"
#include "SexyAppFramework/RtSerial.h"
#include <string.h>

using namespace Sexy;
using namespace Sexy::RtSerial;

// Calls a writer method with the current key: none inside an array, the top of mKeyStack otherwise.
#define WRITE_KEYED(xParser, xCall, ...) \
	if (!xParser->mInArrayStack.back()) \
		xParser->mWriter->xCall(xParser->mKeyStack.back(), ##__VA_ARGS__); \
	else \
		xParser->mWriter->xCall(NULL, ##__VA_ARGS__)

/////////////// Lifecycle ///////////////

JsonParser::JsonParser()
: mParser(NULL)
, mWriter(NULL)
{
}

JsonParser::~JsonParser()
{
	if (mParser)
		mParser->PrsDestroy();
}

/////////////// Parsing ///////////////

void JsonParser::Clear()
{
	mInArrayStack.clear();
	mKeyStack.clear();
	mCountingStack.clear();
	mCountStack.clear();
	mWriter = NULL;
}

void JsonParser::ExecuteTree(FEAST::IPrsNode* inRoot)
{
	struct Local
	{
		static std::string GetLexeme(FEAST::SLexToken* inToken)
		{
			std::string buffer;
			buffer.reserve(inToken->mLexemeLen + 2);
			buffer.resize(inToken->mLexemeLen + 2);
			char* str = (char*)buffer.c_str();
			memcpy(str, inToken->mLexeme, inToken->mLexemeLen);
			str[inToken->mLexemeLen] = 0;
			return str;
		}

		static bool IsJsonStringWide(const std::string& inStr)
		{
			int length = inStr.length();
			const char* str = inStr.c_str();
			for (int i = 0; i < length; i++, str++)
			{
				if (*str != '\\')
					continue;
				i++;
				str++;
				if (i >= length)
					return false;
				if (*str == 'u')
				{
					int code = 0;
					for (int n = 0; n < 4; n++)
					{
						i++;
						str++;
						if (i >= length)
							break;
						unsigned char c = *str;
						code <<= 4;
						if (c >= '0' && c <= '9')
							code |= c - '0';
						else if (c >= 'A' && c <= 'F')
							code |= c - 'A' + 10;
						else if (c >= 'a' && c <= 'f')
							code |= c - 'a' + 10;
						else
							break;
					}
					if (code > 255)
						return true;
				}
			}
			return false;
		}

		static std::string UnicodeToUTF8(int inCode)
		{
			std::string result;
			if (inCode < 0x80)
			{
				result += (char)inCode;
			}
			else if (inCode < 0x800)
			{
				result += (char)((inCode >> 6) | 0xc0);
				result += (char)((inCode & 0x3f) | 0x80);
			}
			else if (inCode < 0x10000)
			{
				result += (char)((inCode >> 12) | 0xe0);
				result += (char)(((inCode >> 6) & 0x3f) | 0x80);
				result += (char)((inCode & 0x3f) | 0x80);
			}
			else if (inCode <= 0x10ffff)
			{
				result += (char)((inCode >> 18) | 0xf0);
				result += (char)(((inCode >> 12) & 0x3f) | 0x80);
				result += (char)(((inCode >> 6) & 0x3f) | 0x80);
				result += (char)((inCode & 0x3f) | 0x80);
			}
			return result;
		}

		static void ProcessJsonString(std::string& outStr, const std::string& inStr)
		{
			int length = inStr.length();
			const char* str = inStr.c_str();
			for (int i = 0; i < length; i++, str++)
			{
				if (*str != '\\')
				{
					outStr += *str;
					continue;
				}
				i++;
				str++;
				if (i >= length)
					break;
				switch (*str)
				{
				case '"': outStr += '"'; break;
				case '/': outStr += '/'; break;
				case '\\': outStr += '\\'; break;
				case 'b': outStr += '\b'; break;
				case 'f': outStr += "\f"; break;
				case 'n': outStr += "\n"; break;
				case 'r': outStr += "\r"; break;
				case 't': outStr += "\t"; break;
				case 'u':
				{
					int code = 0;
					for (int n = 0; n < 4; n++)
					{
						i++;
						str++;
						if (i >= length)
							break;
						unsigned char c = *str;
						code <<= 4;
						if (c >= '0' && c <= '9')
							code |= c - '0';
						else if (c >= 'A' && c <= 'F')
							code |= c - 'A' + 10;
						else if (c >= 'a' && c <= 'f')
							code |= c - 'a' + 10;
						else
							break;
					}
					outStr += UnicodeToUTF8(code);
					break;
				}
				default:
					outStr += *str;
					break;
				}
			}
		}

		static void ProcessJsonStringW(std::wstring& outStr, const std::string& inStr)
		{
			int length = inStr.length();
			const char* str = inStr.c_str();
			for (int i = 0; i < length; i++, str++)
			{
				if (*str != '\\')
				{
					outStr += (wchar_t)*str;
					continue;
				}
				i++;
				str++;
				if (i >= length)
					break;
				switch (*str)
				{
				case '"': outStr += L'"'; break;
				case '/': outStr += L'/'; break;
				case '\\': outStr += L'\\'; break;
				case 'b': outStr += L'\b'; break;
				case 'f': outStr += L"\f"; break;
				case 'n': outStr += L"\n"; break;
				case 'r': outStr += L"\r"; break;
				case 't': outStr += L"\t"; break;
				case 'u':
				{
					int code = 0;
					for (int n = 0; n < 4; n++)
					{
						i++;
						str++;
						if (i >= length)
							break;
						unsigned char c = *str;
						code <<= 4;
						if (c >= '0' && c <= '9')
							code |= c - '0';
						else if (c >= 'A' && c <= 'F')
							code |= c - 'A' + 10;
						else if (c >= 'a' && c <= 'f')
							code |= c - 'a' + 10;
						else
							break;
					}
					outStr += (wchar_t)code;
					break;
				}
				default:
					outStr += (wchar_t)*str;
					break;
				}
			}
		}

		static void ExecuteNode(JsonParser* parser, FEAST::IPrsNode* inNode)
		{
			if (!inNode)
				return;

			switch (inNode->NodeGetTag())
			{
			case NODE_STRING:
			{
				std::string str = GetLexeme(inNode->NodeGetToken());
				str = str.substr(1, str.size() - 2);
				if (RtId::IsRtIdString(str))
				{
					const RtId::OfflineId& id = RtId::OfflineId::StaticParse(str);
					WRITE_KEYED(parser, WriteRtId, id);
				}
				else if (IsJsonStringWide(str))
				{
					std::wstring value;
					ProcessJsonStringW(value, str);
					WRITE_KEYED(parser, WriteUTF8String, value, true);
				}
				else
				{
					std::string value;
					ProcessJsonString(value, str);
					WRITE_KEYED(parser, WriteString, value, true);
				}
				break;
			}
			case NODE_FLOAT:
			{
				std::string str = GetLexeme(inNode->NodeGetToken());
				double value = atof(str.c_str());
				if ((float)value == value)
				{
					WRITE_KEYED(parser, WriteFloat, (float)value);
				}
				else
				{
					WRITE_KEYED(parser, WriteDouble, value);
				}
				break;
			}
			case NODE_DECINTEGER:
			{
				std::string str = GetLexeme(inNode->NodeGetToken());
				int value = atoi(str.c_str());
				WRITE_KEYED(parser, WriteInt32, value);
				break;
			}
			case NODE_HEXINTEGER:
			{
				std::string str = GetLexeme(inNode->NodeGetToken());
				int value;
				StringToInt(str, &value);
				WRITE_KEYED(parser, WriteInt32, value);
				break;
			}
			case NODE_LIST:
				ExecuteNode(parser, inNode->NodeGetChild(0));
				ExecuteNode(parser, inNode->NodeGetChild(1));
				break;
			case NODE_EMPTY_OBJECT:
				if (parser->mInArrayStack.empty())
					parser->mWriter->BeginDocumentObject();
				else
				{
					WRITE_KEYED(parser, BeginObject);
				}

				if (parser->mInArrayStack.empty())
					parser->mWriter->EndDocumentObject();
				else
					parser->mWriter->EndObject();
				break;
			case NODE_OBJECT:
				if (parser->mInArrayStack.empty())
					parser->mWriter->BeginDocumentObject();
				else
				{
					WRITE_KEYED(parser, BeginObject);
				}

				parser->mInArrayStack.push_back(false);
				ExecuteListNode(parser, inNode->NodeGetChild(0));
				parser->mInArrayStack.pop_back();

				if (parser->mInArrayStack.empty())
					parser->mWriter->EndDocumentObject();
				else
					parser->mWriter->EndObject();
				break;
			case NODE_EMPTY_ARRAY:
				WRITE_KEYED(parser, BeginArray, 0);
				parser->mWriter->EndArray();
				break;
			case NODE_ARRAY: // walked once to count the elements, once to write them
			{
				parser->mCountingStack.push_back(true);
				parser->mCountStack.push_back(0);
				parser->mInArrayStack.push_back(true);
				ExecuteListNode(parser, inNode->NodeGetChild(0));
				parser->mInArrayStack.pop_back();
				int count = parser->mCountStack.back();
				parser->mCountStack.pop_back();
				parser->mCountingStack.pop_back();

				WRITE_KEYED(parser, BeginArray, count);

				parser->mCountingStack.push_back(false);
				parser->mInArrayStack.push_back(true);
				ExecuteListNode(parser, inNode->NodeGetChild(0));
				parser->mInArrayStack.pop_back();
				parser->mCountingStack.pop_back();
				parser->mWriter->EndArray();
				break;
			}
			case NODE_KVP:
			{
				std::string key = GetLexeme(inNode->NodeGetChild(0)->NodeGetToken());
				key = key.substr(1, key.size() - 2);
				std::string processed;
				ProcessJsonString(processed, key);
				parser->mKeyStack.push_back(processed);
				ExecuteNode(parser, inNode->NodeGetChild(1));
				parser->mKeyStack.pop_back();
				break;
			}
			case NODE_ELEMENT:
				if (parser->mCountingStack.back())
					parser->mCountStack.back()++;
				else
					ExecuteNode(parser, inNode->NodeGetChild(0));
				break;
			case NODE_TRUE:
				WRITE_KEYED(parser, WriteBool, true);
				break;
			case NODE_FALSE:
				WRITE_KEYED(parser, WriteBool, false);
				break;
			case NODE_NULL:
				WRITE_KEYED(parser, WriteRtId, RtId());
				break;
			}
		}

		static void ExecuteListNode(JsonParser* parser, FEAST::IPrsNode* inNode)
		{
			std::vector<FEAST::IPrsNode*> nodes;
			FEAST::IPrsNode* node = inNode;
			while (node)
			{
				if (node->NodeGetTag() == NODE_LIST)
				{
					nodes.push_back(node->NodeGetChild(1));
					node = node->NodeGetChild(0);
				}
				else
				{
					nodes.push_back(node);
					node = NULL;
				}
			}
			int count = nodes.size();
			for (int i = count - 1; i >= 0; i--)
				ExecuteNode(parser, nodes[i]);
		}
	};

	Local::ExecuteNode(this, inRoot);
}
