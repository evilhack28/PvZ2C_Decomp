//
//  PowerupMiniGamePerkRefreshCard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "PowerupMiniGamePerk.h"
#include "AudioMgr.h"

/////////////// PowerupMiniGamePerkRefreshCard ///////////////

RT_CLASS_IMPLEMENT(PowerupMiniGamePerkRefreshCard);

bool PowerupMiniGamePerkRefreshCard::canActivate()
{
	return true;
}

void PowerupMiniGamePerkRefreshCard::onEnterState_Activated(PowerupState i_fromState)
{
	gAudioMgr->SendEvent("Play_UI_MiniGame_VaseBreak_TapReveal");
}
