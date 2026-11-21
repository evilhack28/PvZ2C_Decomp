//
//  SexyFunctions.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/MTRand.h"

bool isws(wchar_t theChar);

namespace Sexy
{

/////////////// String conversion ///////////////

SexyString StringToSexyString(const std::string& theString)
{
	return StringToWString(theString);
}

SexyString ToSexyString(const std::string& theString)
{
	return StringToSexyString(theString);
}

SexyString WStringToSexyString(const std::wstring& theString)
{
	return theString;
}

std::string SexyStringToString(const SexyString& theString)
{
	return WStringToString(theString);
}

/////////////// Case conversion ///////////////

std::string Upper(const std::string& theData)
{
	std::string aString = theData;
	std::transform(aString.begin(), aString.end(), aString.begin(), toupper);
	return aString;
}

std::string Lower(const std::string& theData)
{
	std::string aString = theData;
	std::transform(aString.begin(), aString.end(), aString.begin(), tolower);
	return aString;
}

std::wstring Upper(const std::wstring& theData)
{
	std::wstring aString = theData;
	std::transform(aString.begin(), aString.end(), aString.begin(), (int (*)(int))towupper);
	return aString;
}

std::string StringToUpper(const std::string& theString)
{
	std::string aString;
	aString.reserve(theString.length());
	for (unsigned int i = 0; i < theString.length(); i++)
		aString += toupper((unsigned char)theString[i]);
	return aString;
}

std::wstring StringToUpper(const std::wstring& theString)
{
	std::wstring aString;
	aString.reserve(theString.length());
	for (unsigned int i = 0; i < theString.length(); i++)
		aString += towupper(theString[i]);
	return aString;
}

std::wstring StringToWString(const std::string& theString)
{
	std::wstring aString;
	aString.reserve(theString.length());
	for (size_t i = 0; i < theString.length(); i++)
		aString += (unsigned char)theString[i];
	return aString;
}

/////////////// Trimming ///////////////

std::string Trim(const std::string& theString)
{
	int aStartPos = 0;
	while (aStartPos < (int)theString.length() && isspace((unsigned char)theString[aStartPos]))
		aStartPos++;

	int anEndPos = theString.length() - 1;
	while (anEndPos >= 0 && isspace((unsigned char)theString[anEndPos]))
		anEndPos--;

	return theString.substr(aStartPos, anEndPos - aStartPos + 1);
}

std::wstring Trim(const std::wstring& theString)
{
	int aStartPos = 0;
	while (aStartPos < (int)theString.length() && isws(theString[aStartPos]))
		aStartPos++;

	int anEndPos = theString.length() - 1;
	while (anEndPos >= 0 && isws(theString[anEndPos]))
		anEndPos--;

	return theString.substr(aStartPos, anEndPos - aStartPos + 1);
}

/////////////// Formatting ///////////////

std::string StrFormat(const char* fmt ...)
{
	va_list argList;
	va_start(argList, fmt);
	std::string result = vformat(fmt, argList);
	va_end(argList);

	return result;
}

std::wstring StrFormat(const wchar_t* fmt ...)
{
	va_list argList;
	va_start(argList, fmt);
	std::wstring result = vformat(fmt, argList);
	va_end(argList);

	return result;
}

void OutputDebugStrF(const char* fmt ...)
{
}

std::wstring UTF8StringToWString(const std::string& theString)
{
	std::wstring aString;
	int aLen = theString.length();
	const char* aPtr = theString.c_str();
	const char* anEndPtr = aPtr + aLen;
	wchar_t aChar;

	while (aPtr < anEndPtr && aLen > 0)
	{
		int aNumChars = GetNextUTF8CharFromStream(&aPtr, aLen, &aChar);
		if (aNumChars == 0)
			break;

		aLen -= aNumChars;
		aString += aChar;
	}

	return aString;
}

/////////////// Random ///////////////

int Rand()
{
	return gCommonMTRand.Next();
}

int Rand(int range)
{
	return gCommonMTRand.Next((ulong)range);
}

float Rand(float range)
{
	return gCommonMTRand.Next(range);
}

void SRand(ulong theSeed)
{
	gCommonMTRand.SRand(theSeed);
}

bool IsNear(float a, float b, float tolerance)
{
	return fabsf(a - b) < tolerance;
}

} // namespace Sexy
