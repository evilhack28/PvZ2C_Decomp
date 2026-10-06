//
//  JoustOrAdventureScreenTopHUD.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "JoustOrAdventureScreenTopHUD.h"

JoustOrAdventureScreenTopHUD::JoustOrAdventureScreenTopHUD()
{
}

JoustOrAdventureScreenTopHUD::~JoustOrAdventureScreenTopHUD()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustOrAdventureScreenTopHUD);

void JoustOrAdventureScreenTopHUD::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustOrAdventureScreenTopHUD);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZGameStateTopHUDController);

	REFLECTION_CLASSBUILDER_END(JoustOrAdventureScreenTopHUD);
}

void JoustOrAdventureScreenTopHUD::onShowingFUEChanged(bool i_arg)
{
	m_showingFUE = i_arg;
}
