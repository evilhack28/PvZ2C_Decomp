//
//  JoustOrAdventureScreenState.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "JoustOrAdventureScreenState.h"
#include "ReflectionBuilder.h"
#include "AdaptorJoustOrAdventureScreen.h"
#include "JoustOrAdventureScreenTopHUD.h"

/////////////// Lifecycle ///////////////

JoustOrAdventureScreenState::JoustOrAdventureScreenState()
{
}

JoustOrAdventureScreenState::~JoustOrAdventureScreenState()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(JoustOrAdventureScreenState);

void JoustOrAdventureScreenState::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustOrAdventureScreenState);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZHotUIGameState);

	REFLECTION_CLASSBUILDER_END(JoustOrAdventureScreenState);
}

/////////////// Logic ///////////////

RtClass* JoustOrAdventureScreenState::getHotUIAdaptorClass()
{
	return AdaptorJoustOrAdventureScreen::StaticGetClass();
}

RtClass* JoustOrAdventureScreenState::getTopHudControllerClass()
{
	return JoustOrAdventureScreenTopHUD::StaticGetClass();
}
