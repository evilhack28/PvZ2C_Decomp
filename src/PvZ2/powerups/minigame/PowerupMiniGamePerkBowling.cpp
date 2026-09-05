//
//  PowerupMiniGamePerkBowling.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "PowerupMiniGamePerk.h"
#include "AudioMgr.h"

/////////////// PowerupMiniGamePerkBowling ///////////////

RT_CLASS_IMPLEMENT(PowerupMiniGamePerkBowling);

bool PowerupMiniGamePerkBowling::canActivate()
{
	return true;
}

void PowerupMiniGamePerkBowling::onEnterState_Activated(PowerupState i_fromState)
{
	gAudioMgr->SendEvent("Play_UI_MiniGame_VaseBreak_TapReveal");
}
