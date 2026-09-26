//
//  JoustLandingScreenTopHUD.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "JoustLandingScreenTopHUD.h"

JoustLandingScreenTopHUD::JoustLandingScreenTopHUD()
{
}

JoustLandingScreenTopHUD::~JoustLandingScreenTopHUD()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustLandingScreenTopHUD);

void JoustLandingScreenTopHUD::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustLandingScreenTopHUD);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PVZGameStateTopHUDController);

	REFLECTION_CLASSBUILDER_END(JoustLandingScreenTopHUD);
}
