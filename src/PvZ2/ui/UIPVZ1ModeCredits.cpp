//
//  UIPVZ1ModeCredits.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "UIPVZ1ModeCredits.h"
#include "LawnApp.h"

void UIPVZ1ModeCredits::PlayEndFunc()
{
}

void UIPVZ1ModeCredits::InitView()
{
}

UIPVZ1ModeCredits::UIPVZ1ModeCredits()
{
}

UIPVZ1ModeCredits::~UIPVZ1ModeCredits()
{
}

bool UIPVZ1ModeCredits::OnCreate()
{
	bool result = UI::Dialog::OnCreate();

	Sexy::Widget* background = GetWidget("Background_0");
	background->mX = (gLawnApp->mScreenBounds.mWidth - background->mWidth) / 2;

	Sexy::Widget* playButton = GetWidget("PlayBtn");
	playButton->SetVisible(false);

	return result;
}

void UIPVZ1ModeCredits::Draw(Sexy::Graphics* i_g)
{
	UI::Dialog::Draw(i_g);
}

void UIPVZ1ModeCredits::ButtonDepress(int i_id)
{
	if (i_id == PVZ1Mode_Credits_BackToMain)
		CloseDialog();
}
