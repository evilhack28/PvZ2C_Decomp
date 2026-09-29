//
//  ZombieIceAgeChiefElite.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeChief.h"

ZombieIceAgeChiefEliteProps::~ZombieIceAgeChiefEliteProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeChiefElite);

void ZombieIceAgeChiefElite::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeChiefElite);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieIceAgeChief);

	REFLECTION_CLASSBUILDER_END(ZombieIceAgeChiefElite);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeChiefEliteProps);

void ZombieIceAgeChiefEliteProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeChiefEliteProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieIceAgeChiefProps);

	REFLECTION_CLASSBUILDER_END(ZombieIceAgeChiefEliteProps);
}
