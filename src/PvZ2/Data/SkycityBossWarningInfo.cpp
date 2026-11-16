//
//  SkycityBossWarningInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SkycityBossWarningInfo.h"
#include "SexyAppFramework/Graphics.h"
#include "LawnApp.h"

static WEAKIMAGE(IMAGE_UI_HUD_INGAME_BOSSWARNING, "IMAGE_UI_HUD_INGAME_BOSSWARNING");

/////////////// Lifecycle ///////////////

SkycityBossWarningInfo::SkycityBossWarningInfo()
{
}

SkycityBossWarningInfo::~SkycityBossWarningInfo()
{
}

/////////////// Update ///////////////

void SkycityBossWarningInfo::Update()
{
	if (isUp)
	{
		float per = redlayerPer + 0.05f;
		if (per >= 1.0f)
		{
			redlayerPer = 1.0f;
			isUp = false;
			return;
		}
		redlayerPer = per;
	}
	else
	{
		float per = redlayerPer - 0.05f;
		if (per <= 0.0f)
		{
			per = 0.0f;
			isUp = true;
		}
		redlayerPer = per;
	}
}

/////////////// Draw ///////////////

void SkycityBossWarningInfo::DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g)
{
	DrawRedLayer(g);
	DrawRedImg(g);
	Sexy::WidgetContainer::DrawAll(theFlags, g);
}

void SkycityBossWarningInfo::DrawRedLayer(Sexy::Graphics* i_g)
{
	Sexy::GraphicsAutoState state(i_g);
	int alpha = (int)(redlayerPer * 128.0f);
	i_g->ClearClipRect();
	i_g->mTransX = 0;
	i_g->mTransY = 0;
	i_g->SetColor(Sexy::Color(255, 0, 0, alpha));
	i_g->FillRect(0, 0, gLawnApp->mScreenBounds.mWidth, gLawnApp->mScreenBounds.mHeight);
}

void SkycityBossWarningInfo::DrawRedImg(Sexy::Graphics* i_g)
{
	Sexy::GraphicsAutoState state(i_g);
	i_g->SetDrawMode(Sexy::Graphics::DRAWMODE_ADDITIVE);
	i_g->SetColorizeImages(true);
	Sexy::Color color(Sexy::Color::White);
	color.mAlpha = (int)(redlayerPer * 255.0f);
	i_g->SetColor(color);
	i_g->DrawImage(IMAGE_UI_HUD_INGAME_BOSSWARNING,
		(gLawnApp->mScreenBounds.mWidth - IMAGE_UI_HUD_INGAME_BOSSWARNING->mWidth) / 2,
		(gLawnApp->mScreenBounds.mHeight - IMAGE_UI_HUD_INGAME_BOSSWARNING->mHeight) / 2);
	i_g->SetDrawMode(Sexy::Graphics::DRAWMODE_NORMAL);
}
