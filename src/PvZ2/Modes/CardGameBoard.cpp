//
//  CardGameBoard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CardGameBoard.h"

void CardGameBoard::ShuffleCards()
{
}

void CardGameBoard::CreateTestInit()
{
}

void CardGameBoard::onBoardCreated()
{
}

void CardGameBoard::CreateTestCards()
{
}

#include "CardGameBoard.h"
void CardGameBoard::Initialize()
{
	 CardGameBoard::CreateBoard();
}

#include "CardGameBoard.h"
void CardGameBoard::OnDrawCard(Card* i_card)
{
	 CardGameBoard::CheckCost();
}

void CardGameBoard::drawTutorials(Sexy::Graphics* i_g)
{
}

#include "CardGameBoard.h"
void CardGameBoard::onBoardPreCreated()
{
	 CardGameBoard::CheckTutorial();
}

#include "CardGameBoard.h"
void CardGameBoard::Update()
{
	 CardGameBoard::updateTutorials();
}
