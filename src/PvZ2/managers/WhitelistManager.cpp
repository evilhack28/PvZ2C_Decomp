//
//  WhitelistManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WhitelistManager.h"
#include "GameEventMgr.h"
#include <algorithm>

WhitelistManager::WhitelistManager()
{
}

WhitelistManager::~WhitelistManager()
{
}

/////////////// Whitelisting ///////////////

void WhitelistManager::DisableAllInput()
{
	EnableWhitelisting(std::vector<std::string>());
}

void WhitelistManager::EnableWhitelisting(const std::string& i_allowedID)
{
	std::vector<std::string> allowedIDs;
	allowedIDs.push_back(i_allowedID);
	EnableWhitelisting(allowedIDs);
}

void WhitelistManager::EnableWhitelisting(const std::vector<std::string>& i_allowedIDs)
{
	DisableWhitelisting();
	m_whitelistingEnabled = true;
	m_allowedWhitelistIDs = i_allowedIDs;
	BroadcastMessage(Message::WhitelistingChanged);
}

void WhitelistManager::DisableWhitelisting()
{
	m_whitelistingEnabled = false;
	m_allowedWhitelistIDs.clear();
	BroadcastMessage(Message::WhitelistingChanged);
}

bool WhitelistManager::IsDisabledByWhitelisting(const std::string& i_whitelistID)
{
	if (m_whitelistingEnabled)
	{
		if (i_whitelistID.empty())
			return true;
		return std::find(m_allowedWhitelistIDs.begin(), m_allowedWhitelistIDs.end(), i_whitelistID) == m_allowedWhitelistIDs.end();
	}
	return false;
}
