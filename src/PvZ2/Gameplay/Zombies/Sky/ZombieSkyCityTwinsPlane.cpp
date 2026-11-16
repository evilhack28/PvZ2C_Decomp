//
//  ZombieSkyCityTwinsPlane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSkyCityTwinsPlane.h"

ZombieSkyCityTwinsPlaneProps::ZombieSkyCityTwinsPlaneProps()
{
}

ZombieSkyCityTwinsPlaneProps::~ZombieSkyCityTwinsPlaneProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkyCityTwinsPlane);

void ZombieSkyCityTwinsPlane::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSkyCityTwinsPlane);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSkyCity);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, m_vHalfHealth);
	REFLECTION_CLASSBUILDER_END(ZombieSkyCityTwinsPlane);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkyCityTwinsPlaneProps);

void ZombieSkyCityTwinsPlaneProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSkyCityTwinsPlaneProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSkyCityProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, DamageFactor);
		REFLECTION_CLASSBUILDER_FIELD(float, EatingSpeed);
		REFLECTION_CLASSBUILDER_FIELD(int, GridInterval);
	REFLECTION_CLASSBUILDER_END(ZombieSkyCityTwinsPlaneProps);
}
