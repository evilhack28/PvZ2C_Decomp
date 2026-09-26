//
//  OakArrowHolderUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "OakArrowHolderUI.h"
#include "Graphics.h"
#include "ResourceHelpers.h"

OakArrowHolderUI::OakArrowHolderUI()
{
}

OakArrowHolderUI::~OakArrowHolderUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(OakArrowHolderUI);

static CachedResourcePtr<Sexy::Image> g_holderBg("IMAGE_UI_HUD_INGAME_OAK_ARROW_HOLDER_BG");

void OakArrowHolderUI::Draw(Graphics* i_g)
{
	UIWidget::Draw(i_g);
	GraphicsAutoState state(i_g);
	translateToWidgetPosition(i_g);
	i_g->DrawImage(g_holderBg.operator->(), 0, 0);
}
