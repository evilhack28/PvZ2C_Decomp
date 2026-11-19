//
//  JsonReader.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/JsonReader.h"
#include "SexyAppFramework/SexyAppBase.h"

using namespace Sexy;

/////////////// Scanning ///////////////

JsonReader::Char JsonReader::GetNextChar()
{
	if (mCurrent < mEnd)
	{
		Char c = *mCurrent++;
		UpdateLineAndColumn(c);
		return c;
	}
	return 0;
}

void JsonReader::UpdateLineAndColumn(Char c)
{
	if (c == '\r' || (c == '\n' && mLineBreakTrackingChar != '\r'))
	{
		mColumn = 1;
		mLine++;
	}
	else
	{
		mColumn++;
	}
	mLineBreakTrackingChar = c;
}

void JsonReader::ScanCommentTokens(Token& token)
{
	do
	{
		ScanToken(token);
	}
	while (token.type == tokenComment);
}

/////////////// Errors ///////////////

bool JsonReader::AddErrorAndRecover(const std::string& message, Token& token, TokenType skipUntilToken)
{
	AddError(message, token);
	return RecoverFromError(skipUntilToken);
}

bool JsonReader::ScanCppStyleComment()
{
	while (mCurrent != mEnd)
	{
		Char c = GetNextChar();
		if (c == '\n')
			return true;
		if (c == '\r')
			return true;
	}
	return true;
}

bool JsonReader::ScanCStyleComment()
{
	while (mCurrent != mEnd)
	{
		Char c = GetNextChar();
		if (c == '*' && *mCurrent == '/')
			break;
	}
	return GetNextChar() == '/';
}

bool JsonReader::ScanComment()
{
	Char c = GetNextChar();
	if (c == '*')
		return ScanCStyleComment();
	if (c == '/')
		return ScanCppStyleComment();
	return false;
}

bool JsonReader::ScanPattern(const char* pattern, int patternLength)
{
	if (mEnd - mCurrent < patternLength)
		return false;

	int i = patternLength;
	while (i--)
	{
		if (mCurrent[i] != pattern[i])
			return false;
	}

	mCurrent += patternLength;
	return true;
}

void JsonReader::ScanWhitespace()
{
	while (mCurrent != mEnd)
	{
		Char c = *mCurrent;
		UpdateLineAndColumn(c);
		if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
			return;
		mCurrent++;
	}
}

bool JsonReader::ScanString()
{
	while (mCurrent != mEnd)
	{
		Char c = GetNextChar();
		if (c == '\\')
		{
			if (mCurrent != mEnd)
				GetNextChar();
		}
		else if (c == '"')
			return true;
	}
	return false;
}

/////////////// Reading ///////////////

bool JsonReader::ReadString(Token& token, String name)
{
	String decoded;
	bool ok = DecodeString(token, decoded);
	if (ok)
		mData->AddString(name, decoded);
	return ok;
}

bool JsonReader::Read(uchar* begin, uchar* end, StructuredData* data, StructuredData* errors)
{
	mEnd = end;
	mBegin = begin;
	mData = data;
	mCurrent = begin;
	mErrors = errors;
	mLine = 1;
	mColumn = 1;
	mLineBreakTrackingChar = 0;

	size_t errorCount = 0;
	if (errors)
	{
		errorCount = errors->Size();
		mErrors->BeginArray("jsonParseErrors");
	}

	bool ok = ReadValue(NULL);

	Token token;
	ScanCommentTokens(token);

	if (mErrors)
	{
		if (ok)
			mErrors->Rewind(errorCount);
		else
			mErrors->EndArray();
	}

	return ok;
}

bool JsonReader::RecoverFromError(TokenType skipUntilToken)
{
	uint32 mark = 0;
	if (mErrors)
		mark = mErrors->Mark();

	Token token;
	do
	{
		ScanToken(token);
		if (token.type == skipUntilToken)
			break;
	}
	while (token.type != tokenEndOfStream);

	if (mErrors)
		mErrors->Rewind(mark);

	return false;
}

JsonReader::Location JsonReader::WriteCodePointToUTF8(uint32 cp, Location out)
{
	int length = 0;
	if (cp < 0x80)
	{
		out[0] = cp;
		length = 1;
	}
	else if (cp < 0x800)
	{
		out[1] = 0x80 | (cp & 0x3F);
		out[0] = 0xC0 | (cp >> 6);
		length = 2;
	}
	else if (cp < 0x10000)
	{
		out[2] = 0x80 | (cp & 0x3F);
		out[1] = 0x80 | ((cp >> 6) & 0x3F);
		out[0] = 0xE0 | (cp >> 12);
		length = 3;
	}
	else if (cp < 0x110000)
	{
		out[3] = 0x80 | (cp & 0x3F);
		out[2] = 0x80 | ((cp >> 6) & 0x3F);
		out[1] = 0x80 | ((cp >> 12) & 0x3F);
		out[0] = 0xF0 | (cp >> 18);
		length = 4;
	}
	return out + length;
}

JsonReader::JsonReader()
{
}

void JsonReader::ScanToken(Token& token)
{
	ScanWhitespace();

	token.start = mCurrent;
	token.line = mLine;
	token.column = mColumn;

	bool ok = true;
	switch (GetNextChar())
	{
	case 0:
		token.type = tokenEndOfStream;
		break;
	case '{':
		token.type = tokenObjectBegin;
		break;
	case '}':
		token.type = tokenObjectEnd;
		break;
	case '[':
		token.type = tokenArrayBegin;
		break;
	case ']':
		token.type = tokenArrayEnd;
		break;
	case '"':
		token.type = tokenString;
		ok = ScanString();
		break;
	case '-':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		token.type = tokenNumber;
		ScanNumber();
		break;
	case 'f':
		token.type = tokenFalse;
		ok = ScanPattern("alse", 4);
		break;
	case 'n':
		token.type = tokenNull;
		ok = ScanPattern("ull", 3);
		break;
	case 't':
		token.type = tokenTrue;
		ok = ScanPattern("rue", 3);
		break;
	case ',':
		token.type = tokenArraySeparator;
		break;
	case ':':
		token.type = tokenMemberSeparator;
		break;
	case '/':
		token.type = tokenComment;
		ok = ScanComment();
		break;
	default:
		ok = false;
		break;
	}

	if (!ok)
		token.type = tokenError;

	token.end = mCurrent;
}

bool JsonReader::ScanExpectedToken(Token& token, TokenType expectedType, const char* errorMessage)
{
	ScanToken(token);
	if (token.type != expectedType)
		return AddError(errorMessage, token);

	return true;
}

bool JsonReader::ReadValue(String name)
{
	Token token;
	ScanCommentTokens(token);

	bool ok;
	switch (token.type)
	{
	case tokenObjectBegin:
		mData->BeginObject(name);
		ok = ReadObject(token);
		mData->EndObject();
		return ok;
	case tokenArrayBegin:
		mData->BeginArray(name);
		ok = ReadArray(token);
		mData->EndArray();
		return ok;
	case tokenString:
		return ReadString(token, name);
	case tokenNumber:
		return DecodeNumber(token, name);
	case tokenTrue:
		mData->AddBoolean(name, true);
		return true;
	case tokenFalse:
		mData->AddBoolean(name, false);
		return true;
	case tokenNull:
		mData->AddNull(name);
		return true;
	default:
		return AddError("Syntax error: value, object or array expected.", token);
	}
}

bool JsonReader::AddError(const std::string& message, Token& token, Location extra)
{
	if (mErrors)
	{
		mErrors->BeginObject(StructuredData::noName);
		mErrors->AddString("message", message.c_str());
		mErrors->BeginObject("token");
		mErrors->AddInteger("type", token.type);
		mErrors->AddInteger("line", token.line);
		mErrors->AddInteger("column", token.column);
		mErrors->EndObject();
		if (extra)
			mErrors->AddInteger("extra", (int)(extra - token.start));
		mErrors->EndObject();
	}
	return false;
}

bool JsonReader::DecodeDouble(Token& token, String name)
{
	char* end;
	double value;
	value = strtod((const char*)token.start, &end);
	if ((Location)end != token.end)
		return AddError("'" + std::string(token.start, token.end) + "' is not a number.", token);

	mData->AddNumber(name, value);
	return true;
}

bool JsonReader::DecodeUnicodeEscapeSequence(Token& token, Location& current, Location end, uint32& unicode)
{
	if (end - current < 4)
		return AddError("Bad unicode escape sequence in string: four digits expected.", token, current);

	unicode = 0;
	for (int index = 0; index < 4; index++)
	{
		Char c = *current++;
		unicode *= 16;
		if (c >= '0' && c <= '9')
			unicode += c - '0';
		else if (c >= 'a' && c <= 'f')
			unicode += c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			unicode += c - 'A' + 10;
		else
			return AddError("Bad unicode escape sequence in string: hexadecimal digit expected.", token, current);
	}
	return true;
}

bool JsonReader::DecodeUnicodeCodePoint(Token& token, Location& current, Location end, uint32& unicode)
{
	if (!DecodeUnicodeEscapeSequence(token, current, end, unicode))
		return false;

	if (unicode >= 0xD800 && unicode <= 0xDBFF)
	{
		if (end - current < 6)
			return AddError("additional six characters expected to parse unicode surrogate pair.", token, current);

		uint32 surrogatePair;
		if (*(current++) == '\\' && *(current++) == 'u')
		{
			if (!DecodeUnicodeEscapeSequence(token, current, end, surrogatePair))
				return false;

			unicode = 0x10000 + ((unicode & 0x3FF) << 10) + (surrogatePair & 0x3FF);
		}
		else
			return AddError("expecting another \\u token to begin the second half of a unicode surrogate pair", token, current);
	}
	return true;
}

bool JsonReader::DecodeString(Token& token, String& decoded)
{
	Location out = token.start;
	Location current = token.start + 1;
	Location end = token.end - 1;
	decoded = (String)out;

	while (current < end)
	{
		Char c = *current++;
		if (c == '"')
			break;

		if (c == '\\')
		{
			if (current == end)
				return AddError("Empty escape sequence in string", token, current);

			Char escape = *current++;
			switch (escape)
			{
			case '"':
				*out++ = '"';
				break;
			case '/':
				*out++ = '/';
				break;
			case '\\':
				*out++ = '\\';
				break;
			case 'b':
				*out++ = '\b';
				break;
			case 'f':
				*out++ = '\f';
				break;
			case 'n':
				*out++ = '\n';
				break;
			case 'r':
				*out++ = '\r';
				break;
			case 't':
				*out++ = '\t';
				break;
			case 'u':
			{
				uint32 unicode;
				if (!DecodeUnicodeCodePoint(token, current, end, unicode))
					return false;
				out = WriteCodePointToUTF8(unicode, out);
				break;
			}
			default:
				return AddError("Bad escape sequence in string", token, current);
			}
		}
		else
		{
			*out++ = c;
		}
	}

	*out = 0;
	return true;
}

bool JsonReader::Inspect(uchar* begin, uchar* end)
{
	mEnd = end;
	mBegin = begin;
	mCurrent = begin;
	mData = NULL;
	mErrors = NULL;
	mLine = 1;
	mColumn = 1;
	mLineBreakTrackingChar = 0;

	Token token;
	ScanCommentTokens(token);

	switch (token.type)
	{
	case tokenObjectBegin:
	case tokenArrayBegin:
		return true;
	default:
		return false;
	}
}
