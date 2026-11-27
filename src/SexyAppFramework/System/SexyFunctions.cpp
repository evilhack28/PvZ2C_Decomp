//
//  SexyFunctions.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/MTRand.h"
#include "SexyAppFramework/IFileDriver.h"
#include "SexyAppFramework/PakLib/PakInterface.h"
#include "SexyAppFramework/SexyThread.h"

#include <EASTL/algorithm.h>

#include <pthread.h>
#include <sched.h>

bool isws(wchar_t theChar);

/////////////// Paths ///////////////

template<typename CharType>
const CharType* GetFileName_(const CharType* inPath);

namespace Sexy
{

template<typename CharType>
static std::basic_string<CharType> GetFileNameString_(const std::basic_string<CharType>& thePath, bool noExtension)
{
	const CharType* aName = GetFileName_(thePath.c_str());
	if (aName == NULL)
		return std::basic_string<CharType>();

	if (noExtension)
	{
		const CharType* aDot = StringReverseFindAnyOfWithCase(aName, CharConv<CharType>::Str(".").c_str());
		if (aDot != NULL)
			return std::basic_string<CharType>(aName, aDot - aName);
	}
	return aName;
}

std::string GetFileName(const std::string& thePath, bool noExtension)
{
	return GetFileNameString_(thePath, noExtension);
}

template<typename StringType, typename ConvFunc>
static StringType GetFileDirString_(const StringType& thePath, bool withSlash)
{
	int aLastBackslash = thePath.rfind(ConvFunc::Char('\\'));
	int aLastSlash = thePath.rfind(ConvFunc::Char('/'));
	int aLastDirPos = eastl::max_alt(aLastBackslash, aLastSlash);
	if (aLastDirPos == -1)
		return ConvFunc::Str("");

	if (withSlash)
		aLastDirPos++;
	return thePath.substr(0, aLastDirPos);
}

std::string GetFileDir(const std::string& thePath, bool withSlash)
{
	return GetFileDirString_<std::string, CharToCharFunc>(thePath, withSlash);
}

void MkDir(const std::string& theDir)
{
	gFileDriver->MakeFolders(theDir);
}

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

int GetNextUTF8CharFromStream(const char** theBuffer, int theLen, wchar_t* theChar)
{
	static const unsigned short aMaskData[] = {
		0xC0,
		0xE0,
		0xF0,
		0xF8,
		0xFC
	};
	if (theLen == 0)
		return 0;

	const char* aBuffer = *theBuffer;

	int aTempChar = int((unsigned char)*aBuffer++);
	if ((aTempChar & 0x80) != 0)
	{
		if ((aTempChar & 0xC0) != 0xC0)
			return 0;

		int aBytesRead[6];
		int* aBytesReadPtr = &aBytesRead[0];

		*aBytesReadPtr++ = aTempChar;

		int aLen;
		for (aLen = 0; aLen < (int)(sizeof(aMaskData) / sizeof(*aMaskData)); ++aLen)
		{
			if ((aTempChar & aMaskData[aLen]) == ((aMaskData[aLen] << 1) & aMaskData[aLen]))
				break;
		}
		if (aLen >= (int)(sizeof(aMaskData) / sizeof(*aMaskData)))
			return 0;

		aTempChar &= ~aMaskData[aLen];
		int aTotalLen = aLen + 1;

		if (aTotalLen < 2 || aTotalLen > 6)
			return 0;

		int anExtraChar = 0;
		while (aLen > 0 && (aBuffer - *theBuffer) < theLen)
		{
			anExtraChar = int((unsigned char)*aBuffer++);
			if ((anExtraChar & 0xC0) != 0x80)
				return 0;

			*aBytesReadPtr++ = anExtraChar;

			aTempChar = (aTempChar << 6) | (anExtraChar & 0x3F);
			--aLen;
		}
		if (aLen > 0)
			return 0;

		bool valid = true;
		switch (aTotalLen)
		{
		case 2:
			valid = !((aBytesRead[0] & 0x3E) == 0);
			break;
		case 3:
			valid = !((aBytesRead[0] & 0x1F) == 0 && (aBytesRead[1] & 0x20) == 0);
			break;
		case 4:
			valid = !((aBytesRead[0] & 0x0F) == 0 && (aBytesRead[1] & 0x30) == 0);
			break;
		case 5:
			valid = !((aBytesRead[0] & 0x07) == 0 && (aBytesRead[1] & 0x38) == 0);
			break;
		case 6:
			valid = !((aBytesRead[0] & 0x03) == 0 && (aBytesRead[1] & 0x3C) == 0);
			break;
		}

		if (!valid)
			return 0;
	}

	int aConsumedCount = aBuffer - *theBuffer;

	if ((aTempChar >= 0xD800 && aTempChar <= 0xDFFF) || (aTempChar >= 0xFFFE && aTempChar <= 0xFFFF))
		return 0;

	*theChar = (wchar_t)aTempChar;

	*theBuffer = aBuffer;
	return aConsumedCount;
}

/////////////// Threads ///////////////

struct SexyThreadArgs
{
	SexyThreadProc mProc;
	void* mParam;
};

static void* SexyThreadStart(void* theArg)
{
	SexyThreadArgs* anArgs = (SexyThreadArgs*)theArg;
	anArgs->mProc(anArgs->mParam);
	delete anArgs;
	pthread_exit(NULL);
}

void LaunchThread(SexyThreadProc proc, void* param, SexyThreadPriority pri)
{
	SexyThreadArgs* anArgs = new SexyThreadArgs;
	anArgs->mProc = proc;
	anArgs->mParam = param;

	pthread_attr_t anAttr;
	pthread_attr_init(&anAttr);
	pthread_attr_setstacksize(&anAttr, 0x10000);
	pthread_attr_setdetachstate(&anAttr, PTHREAD_CREATE_DETACHED);
	pthread_t aThread;
	pthread_create(&aThread, &anAttr, SexyThreadStart, anArgs);
	pthread_attr_destroy(&anAttr);

	float aPriority;
	switch (pri)
	{
	case STP_LOWEST:
		aPriority = 0.0f;
		break;
	case STP_LOW:
		aPriority = 0.25f;
		break;
	case STP_HIGH:
		aPriority = 0.75f;
		break;
	case STP_HIGHEST:
		aPriority = 1.0f;
		break;
	default:
		aPriority = 0.5f;
		break;
	}
	int aMin = sched_get_priority_min(SCHED_OTHER);
	int aMax = sched_get_priority_max(SCHED_OTHER);
	sched_param aParam;
	aParam.sched_priority = (int)(aMin + aPriority * (aMax - aMin));
	pthread_setschedparam(aThread, SCHED_OTHER, &aParam);
}

} // namespace Sexy
