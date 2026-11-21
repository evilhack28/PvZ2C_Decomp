//
//  CardGameUtils.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "CardGameUtils.h"
#include "LawnApp.h"
#include "GameStateMgr.h"

/////////////// Accessors ///////////////

bool CardGameUtils::IsPlayingCardGame()
{
	return gGameStateMgr && gGameStateMgr->GetLevelSource() == LEVELSOURCE_CardGame;
}
