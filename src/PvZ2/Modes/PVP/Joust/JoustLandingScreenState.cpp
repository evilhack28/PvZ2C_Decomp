//
//  JoustLandingScreenState.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "JoustLandingScreenState.h"
#include "ReflectionBuilder.h"
#include "AdaptorJoustScreen.h"
#include "JoustLandingScreenTopHUD.h"

/////////////// Lifecycle ///////////////

JoustLandingScreenState::JoustLandingScreenState()
{
}

JoustLandingScreenState::~JoustLandingScreenState()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(JoustLandingScreenState);

void JoustLandingScreenState::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustLandingScreenState);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZHotUIGameState);

	REFLECTION_CLASSBUILDER_END(JoustLandingScreenState);
}

/////////////// Logic ///////////////

RtClass* JoustLandingScreenState::getHotUIAdaptorClass()
{
	return AdaptorJoustScreen::StaticGetClass();
}

RtClass* JoustLandingScreenState::getTopHudControllerClass()
{
	return JoustLandingScreenTopHUD::StaticGetClass();
}
