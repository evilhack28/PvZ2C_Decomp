//
//  ZombieIceAgeChief.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeChief.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeChief);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeChiefProps);

void ZombieIceAgeChiefProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeChiefProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, WindSpawnInterval);
	REFLECTION_CLASSBUILDER_END(ZombieIceAgeChiefProps);
}
