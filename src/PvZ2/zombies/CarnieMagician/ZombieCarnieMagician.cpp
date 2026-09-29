//
//  ZombieCarnieMagician.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCarnieMagician.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCarnieMagician);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCarnieMagicianProps);

void ZombieCarnieMagicianProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieCarnieMagicianProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, ImmuneToPlantRestrictionSet);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, DisappearDuration);
	REFLECTION_CLASSBUILDER_END(ZombieCarnieMagicianProps);
}
