//
//  PVZ2UIAwardScreen.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PVZ2UIAwardScreen.h"

bool PVZ2UIAwardScreen::onNextStarClick()
{
	return true;
}

void PVZ2UIAwardScreen::addLeafHint()
{
	if (leafWidget)
	{
		delete leafWidget;
		leafWidget = NULL;
	}
}

int PVZ2UIAwardScreen::GetScreenCount() const
{
	return static_cast<int>(m_screens.size());
}

int PVZ2UIAwardScreen::GetCurrentScreen() const
{
	return m_screenIndex;
}
