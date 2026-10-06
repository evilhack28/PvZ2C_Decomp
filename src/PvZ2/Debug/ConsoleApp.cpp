//
//  ConsoleApp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "ConsoleApp.h"
#include "CommandConsole.h"

ConsoleApp* gConsoleApp;

/////////////// Construction ///////////////

ConsoleApp::ConsoleApp()
{
	gConsoleApp = this;
	m_console = NULL;
	gConsole = NULL;
	ConsolePrintf("Console Started");
}

ConsoleApp::~ConsoleApp()
{
	if (m_console)
	{
		if (m_console == gConsole)
			gConsole = NULL;
		mWidgetManager->RemoveWidget(m_console);
		delete m_console;
		m_console = NULL;
	}
}

bool ConsoleApp::DebugKeyDown(int i_key)
{
	bool handled = SuperClass::DebugKeyDown(i_key);
	if (!handled)
	{
		CommandConsole* console = m_console;
		handled = i_key == 0xC0 && console != NULL;
		if (handled)
			console->Hide(!console->GetHidden());
	}
	return handled;
}

/////////////// Logging ///////////////

void ConsoleApp::ConsolePrintf(const char* fmt ...)
{
	va_list args;
	va_start(args, fmt);
	std::string str = Sexy::StrFormat(fmt, args);
	va_end(args);
	ConsolePrintf(0, str.c_str());
}

void ConsoleApp::ConsolePrintf(int i_flags, const char* fmt ...)
{
	if (m_console)
	{
		va_list args;
		va_start(args, fmt);
		std::string str = Sexy::StrFormat(fmt, args);
		va_end(args);
		if (!(i_flags & CONS_LOG_ERR))
		{
			if (__builtin_expect(!(i_flags & CONS_LOG_WARN), 0))
				gConsole->AddLine(Sexy::ToSexyString(str), i_flags & CONS_LOG_WARN, i_flags & CONS_LOG_DISPLAY);
			else
				gConsole->AddLineWarn(Sexy::ToSexyString(str), i_flags & CONS_LOG_ERR, true);
		}
		else
			gConsole->AddLineErr(Sexy::ToSexyString(str), 0, true);
	}
}
