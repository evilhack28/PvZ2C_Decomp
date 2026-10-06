//
//  GuessRatio.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "GuessRatio.h"

static bool IsHit(const GuessRatio& i_ratio)
{
	return Sexy::Rand(1.0f) <= i_ratio._winRatio;
}

/////////////// GuessRatio ///////////////

GuessRatio::GuessRatio(float win)
{
	_winRatio = win;
}

GuessResult GuessRatio::GetResult()
{
	return IsHit(*this) ? Guess_Win : Guess_Lose;
}
