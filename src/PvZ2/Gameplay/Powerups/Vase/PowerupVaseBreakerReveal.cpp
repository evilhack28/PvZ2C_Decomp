//
//  PowerupVaseBreakerReveal.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "PowerupVaseBreaker.h"
#include "GridItemVase.h"
#include "AudioMgr.h"

/////////////// PowerupVaseBreakerReveal ///////////////

RT_CLASS_IMPLEMENT(PowerupVaseBreakerReveal);

bool PowerupVaseBreakerReveal::canActivateOnVase(GridItemVase* i_vase)
{
	if (!i_vase)
		return false;
	if (i_vase->AreContentsRevealed())
		return false;
	return !i_vase->IsBreaking();
}

void PowerupVaseBreakerReveal::activateOnVase(GridItemVase* i_vase)
{
	i_vase->SetContentsRevealed(true);
}

void PowerupVaseBreakerReveal::onEnterState_Activated(PowerupState i_fromState)
{
	gAudioMgr->SendEvent("Play_UI_MiniGame_VaseBreak_TapReveal");
}
