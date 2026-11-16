//
//  Cheats.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-23.
//

#include "SexyAppFramework/Common.h"

#include "Cheats.h"
#include "PVZCheats.h"

/////////////// Cheat ///////////////

RT_CLASS_IMPLEMENT(Cheat);

Cheat* Cheat::SetValidContexts(CheatContext i_context)
{
	m_validContexts = i_context;
	return this;
}

CheatContext Cheat::GetValidContexts() const
{
	return m_validContexts;
}

Cheat* Cheat::SetKeyboardShortcut(char i_key)
{
	m_keyboardShortcut = i_key;
	return this;
}

char Cheat::GetKeyboardShortcut() const
{
	return m_keyboardShortcut;
}

/////////////// CheatToggle ///////////////

RT_CLASS_IMPLEMENT(CheatToggle);

/////////////// CheatToggleAction ///////////////

RT_CLASS_IMPLEMENT(CheatToggleAction);

/////////////// CheatCommand ///////////////

RT_CLASS_IMPLEMENT(CheatCommand);

const CheatCommand::CommandHandler& CheatCommand::GetCommand() const
{
	return m_onActivate;
}

/////////////// CheatManager ///////////////

CheatManager::CheatManager()
	: m_currentContext(CHEATCONTEXT_Initial)
{}

CheatManager::~CheatManager()
{}

Cheat* CheatManager::AddCheat(Cheat* i_cheat)
{
	return NULL;
}

Cheat* CheatManager::GetCheat(const std::string& i_name) const
{
	return NULL;
}

Cheat* CheatManager::GetCheatIgnoreContext(const std::string& i_name) const
{
	return NULL;
}

void CheatManager::SetCheatCachedText(const std::string& i_name, const std::string& i_text)
{
	m_cheatCachedText[i_name] = i_text;
}

const std::string CheatManager::GetCheatCachedText(const std::string& i_name, const std::string& i_defaultText)
{
	if (m_cheatCachedText.find(i_name) == m_cheatCachedText.end())
		return i_defaultText;

	return m_cheatCachedText[i_name];
}

void CheatManager::AddCheatCachedLog(const std::string& i_name, const std::string& i_text, int i_maxLines)
{
	std::string cur = GetCheatCachedText(i_name, "");
	cur += i_text;
	cur = trimToMaxLines(cur, i_maxLines);

	SetCheatCachedText(i_name, cur);
}

std::string CheatManager::trimToMaxLines(const std::string& i_text, int i_maxLines)
{
	int numLines = 0;
	size_t pos = std::string::npos;
	do
	{
		pos = i_text.rfind('\n', pos - 1);
		numLines++;
	} while (pos != std::string::npos && numLines <= i_maxLines);

	if (pos == std::string::npos)
		return i_text;

	return i_text.substr(pos + 1);
}

void CheatManager::SetCurrentContext(CheatContext i_context)
{
	m_currentContext = i_context;
}

CheatContext CheatManager::GetCurrentContext() const
{
	return m_currentContext;
}

bool CheatManager::IsCheatValidForCurrentContext(Cheat* i_cheat) const
{
	return TestFlag(i_cheat->GetValidContexts(), m_currentContext);
}

void CheatManager::CheckShortcuts()
{
	std::map<char, Cheat*> shortcutMap;
	for (std::map<std::string, Cheat*>::iterator it = m_cheats.begin(); it != m_cheats.end(); ++it)
	{
		Cheat* cheat = (*it).second;
		if (cheat && cheat->GetKeyboardShortcut())
		{
			char shortcut = cheat->GetKeyboardShortcut();
			std::map<char, Cheat*>::iterator found = shortcutMap.find(shortcut);
			if (found == shortcutMap.end())
			{
				shortcutMap[shortcut] = cheat;
			}
			else
			{
				const std::pair<const char, Cheat*>& collision = *found;
				Sexy::OutputDebugStrF("* Potential cheat keyboard shortcut ('%c') collision between '%s' and '%s'!\n",
					collision.first, cheat->GetName().c_str(), collision.second->GetName().c_str());
			}
		}
	}
}

float CheatManager::GetVariableValue(const std::string& i_name) const
{
	return FLT_MAX;
}

void CheatManager::SetVariableValue(const std::string& i_name, float i_newValue)
{
	Cheat* cheat = GetCheatIgnoreContext(i_name);
	if (cheat && cheat->IsA<CheatVariable>())
		cheat->CastChecked<CheatVariable>()->SetValue(i_newValue);
}

bool CheatManager::GetToggleValue(const std::string& i_name) const
{
	return false;
}

bool CheatManager::SetToggleValue(const std::string& i_name, bool i_newValue)
{
	if (GetToggleValue(i_name) == i_newValue)
		return i_newValue;

	return ToggleCheat(i_name);
}

bool CheatManager::ToggleCheat(const std::string& i_name)
{
	return false;
}

void CheatManager::DoCheatCommand(const std::string& i_name) const
{
}

bool CheatManager::ActivateCheatForKeyboardShortcut(char i_key)
{
	return false;
}
