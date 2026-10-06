//
//  TodDebug.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "TodLib/TodDebug.h"
#include "TodLib/TodCommon.h"

#include "SexyAppFramework/PerfTimer.h"

#include <stdarg.h>
#include <stdio.h>

/////////////// TodDebug ///////////////

void TodHesitationStartBuffer()
{
}

void TodHesitationEndBuffer()
{
}

void TodHesitationTrace(const char* theFormat, ...)
{
}

void TodErrorMessageBox(const char* theMessage, const char* theTitle)
{
}

void TodMemoryDetectLeaks()
{
}

void TodMemoryTraceAllocations()
{
}

void TodAssertInitForApp(BetaSubmitFuncType theFunc)
{
}

void TodVsnprintfEnsureNewLine(char* theBuffer, int theSize, const char* theFormat, va_list theArgList)
{
}

int TodVsnprintf(char* theBuffer, int theSize, const char* theFormat, va_list theArgList)
{
	int aResult = vsnprintf(theBuffer, theSize, theFormat, theArgList);
	if (aResult == -1)
	{
		theBuffer[theSize - 1] = '\0';
		aResult = theSize - 1;
	}
	return aResult;
}

int TodSnprintf(char* theBuffer, int theSize, const char* theFormat, ...)
{
	va_list aArgList;
	va_start(aArgList, theFormat);
	int aResult = TodVsnprintf(theBuffer, theSize, theFormat, aArgList);
	va_end(aArgList);
	return aResult;
}

class HesitationBuffer
{
public:
	HesitationBuffer();

	int m_messageCount;
	Sexy::PerfTimer m_timer;
	int m_startTime;
	int m_endTime;
	bool m_enabled;
	bool m_started;
};

HesitationBuffer::HesitationBuffer()
{
	m_messageCount = 0;
	m_startTime = 0;
	m_enabled = true;
	m_endTime = 0;
	m_started = false;
}

TodHesitationBracket::TodHesitationBracket(const char* theFormat, ...)
{
}
