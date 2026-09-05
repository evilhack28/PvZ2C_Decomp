//
//  PowerupMiniGamePerkTimeBack.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "PowerupMiniGamePerk.h"
#include "AudioMgr.h"

/////////////// PowerupMiniGamePerkTimeBack ///////////////

RT_CLASS_IMPLEMENT(PowerupMiniGamePerkTimeBack);

bool PowerupMiniGamePerkTimeBack::canActivate()
{
	return true;
}

void PowerupMiniGamePerkTimeBack::onEnterState_Activated(PowerupState i_fromState)
{
	gAudioMgr->SendEvent("Play_UI_MiniGame_VaseBreak_TapReveal");
}
