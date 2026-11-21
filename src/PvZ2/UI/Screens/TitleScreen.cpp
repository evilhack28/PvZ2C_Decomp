//
//  TitleScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "TitleScreen.h"

float TitleScreen::GetFirstDecompressTotalAmount()
{
	return 0.2f;
}

float TitleScreen::GetSecondDecompressTotalAmount()
{
	return 0.8f;
}

void TitleScreen::SetState(TitleState i_titleState)
{
	if (m_titleState != i_titleState)
	{
		m_titleState = i_titleState;
		m_stateEnterTime = PVZ_T();
	}
}
