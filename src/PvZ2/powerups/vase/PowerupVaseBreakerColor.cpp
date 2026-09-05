//
//  PowerupVaseBreakerColor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "PowerupVaseBreaker.h"
#include "GridItemVase.h"

/////////////// PowerupVaseBreakerColor ///////////////

RT_CLASS_IMPLEMENT(PowerupVaseBreakerColor);

bool PowerupVaseBreakerColor::canActivateOnVase(GridItemVase* i_vase)
{
	if (!i_vase)
		return false;
	if (i_vase->DoColorByContents())
		return false;
	if (i_vase->AreContentsRevealed())
		return false;
	return !i_vase->IsBreaking();
}

void PowerupVaseBreakerColor::activateOnVase(GridItemVase* i_vase)
{
	i_vase->SetColorByContents(true);
}
