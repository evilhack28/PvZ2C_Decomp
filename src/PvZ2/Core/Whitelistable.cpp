//
//  Whitelistable.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Whitelistable.h"
#include "GameEventMgr.h"
#include "RtDelegate.h"
#include "WhitelistManager.h"

Whitelistable::Whitelistable()
{
}

void Whitelistable::RegisterForWhitelistEvents()
{
	gMessageRouter->Subscribe(Message::WhitelistingChanged, Sexy::MakeDelegate(*this, &Whitelistable::onWhitelistingChanged));
}

void Whitelistable::UnregisterForWhitelistEvents()
{
	gMessageRouter->Unsubscribe(Message::WhitelistingChanged, Sexy::MakeDelegate(*this, &Whitelistable::onWhitelistingChanged));
}

void Whitelistable::SetWhitelistID(const std::string& i_whitelistID)
{
	m_whitelistID = i_whitelistID;
	onWhitelistingChanged();
}

bool Whitelistable::isDisabledByWhitelisting()
{
	return Sexy::LazySingleton<WhitelistManager>::GetInstance().IsDisabledByWhitelisting(m_whitelistID);
}
