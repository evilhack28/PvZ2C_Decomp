//
//  CardBoardMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "CardGameBoard.h"

void CardBoardMgr::CreateBoard()
{
	CardGameBoard::create();
}

const class CardGameBoardConfig* CardBoardMgr::GetConfig() const
{
	return CardBoardMgr::getConfig();
}

int CardBoardMgr::GetInitialHandCardsCount()
{
	return m_initialCardsCount;
}
