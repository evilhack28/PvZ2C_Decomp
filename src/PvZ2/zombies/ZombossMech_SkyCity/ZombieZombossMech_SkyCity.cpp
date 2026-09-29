//
//  ZombieZombossMech_SkyCity.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_SkyCity.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMech_SkyCity);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMechSkyCityProps);

void ZombieZombossMechSkyCityProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMechSkyCityProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMechProps);

		REFLECTION_CLASSBUILDER_FIELD(bool, CanTakeThunder);
	REFLECTION_CLASSBUILDER_END(ZombieZombossMechSkyCityProps);
}

bool ZombieZombossMech_SkyCity::isPlantAllowedUnderZomboss(const PlantType* i_arg)
{
	return true;
}
