//
//  ConsoleListener.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "ConsoleListener.h"
#include "ConsoleApp.h"
#include "CommandConsole.h"

/////////////// Console ///////////////

bool ConsoleEnsureArgs(const CCStringVector& i_params, int i_count)
{
	return i_count == (int)i_params.size();
}

void ConsoleListener::DefineConsoleCommands()
{
	m_consoleDefineMode = true;
	HandleConsoleCommand(_S(""), CCStringVector());
	m_consoleDefineMode = false;
}

bool ConsoleListener::AddConsoleAction(const SexyString& i_passedCmd, const CCStringVector& i_passedParams, int i_context, const SexyString& i_cmd, const SexyString& i_desc, int i_argCount, bool i_addButton)
{
	CommandConsole* console = gConsoleApp->m_console;
	if (console == NULL)
		return false;
	if (m_consoleDefineMode)
	{
		console->AddCommand(i_context, i_cmd, i_desc, i_addButton, fastdelegate::MakeDelegate(this, &ConsoleListener::HandleConsoleCommand));
		return false;
	}
	if (i_passedCmd == i_cmd && ConsoleEnsureArgs(i_passedParams, i_argCount))
	{
		bool echo = m_consoleEchoOn;
		if (echo)
		{
			std::string line = Sexy::StrFormat("^8888ff^--> %S", i_cmd.c_str());
			for (unsigned int i = 0; i < i_passedParams.size(); i++)
				line = Sexy::StrFormat("%s %S", line.c_str(), i_passedParams[i].c_str());
		}
		return echo ? echo : true;
	}
	return false;
}
