//
//  BoardConstants.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "BoardConstants.h"

#include "CardGameUtils.h"
#include "NewPVPUtils.h"

bool BoardConstants::IsCardGameScale()
{
	return CardGameUtils::IsPlayingCardGame();
}

bool BoardConstants::IsNewPVPScale()
{
	return NewPVPUtils::IsPlayingNewPVP();
}
