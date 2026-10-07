//
//  Board.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Board.h"
#include "BoardPropertySheet.h"

bool Board::IsMiniBoard()
{
	return false;
}

void Board::DestroyZomboss()
{
}

void Board::EndCannonLevel()
{
}

void Board::OnAppResumeFocus()
{
}

void Board::onZombieWarningEffectStarted()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Board);

#include "Board.h"
void Board::OnAppLostFocus()
{
	 Board::PauseOnInterrupt();
}

void Board::OnPauseAdFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason)
{
}

#include "Board.h"
void Board::onAppEnteredBackground()
{
	 Board::PauseOnInterrupt();
}

#include "Board.h"
void Board::OnRechargeCurrencyChanged()
{
	 Board::checkAutoSunCollect();
}

void Board::KeyChar(SexyChar i_char)
{
}

void Board::KeyDown(KeyCode i_key)
{
}
