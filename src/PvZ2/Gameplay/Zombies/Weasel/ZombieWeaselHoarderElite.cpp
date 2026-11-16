//
//  ZombieWeaselHoarderElite.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieChickenFarmer.h"

ZombieWeaselHoarderEliteProps::~ZombieWeaselHoarderEliteProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieWeaselHoarderElite);

void ZombieWeaselHoarderElite::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieWeaselHoarderElite);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWeaselHoarder);

	REFLECTION_CLASSBUILDER_END(ZombieWeaselHoarderElite);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieWeaselHoarderEliteProps);

void ZombieWeaselHoarderEliteProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieWeaselHoarderEliteProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieChickenFarmerProps);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, SpawnWeaselInterval);
	REFLECTION_CLASSBUILDER_END(ZombieWeaselHoarderEliteProps);
}
