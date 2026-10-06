//
//  ZombieZombossMech_Dark.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_Dark.h"

ZombieZombossMechDarkProps::~ZombieZombossMechDarkProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMech_Dark);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMechDarkProps);

void ZombieZombossMechDarkProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMechDarkProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMechProps);

		REFLECTION_CLASSBUILDER_FIELD(float, MagnetStunDuration);
	REFLECTION_CLASSBUILDER_END(ZombieZombossMechDarkProps);
}

bool ZombieZombossMech_Dark::isPlantAllowedUnderZomboss(const PlantType* i_arg)
{
	return true;
}
