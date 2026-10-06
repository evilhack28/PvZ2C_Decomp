//
//  ZombieAnimRig_TwinsPlane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSkyCityTwinsPlane.h"

ZombieAnimRig_TwinsPlane::ZombieAnimRig_TwinsPlane()
{
}

ZombieAnimRig_TwinsPlane::~ZombieAnimRig_TwinsPlane()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_TwinsPlane);

void ZombieAnimRig_TwinsPlane::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_TwinsPlane);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_SkyCity);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_TwinsPlane);
}
