//
//  Plant_Blover.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Blover.h"

PlantBlover::PlantBlover()
{
}

PlantBlover::~PlantBlover()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBlover);

void PlantBlover::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBlover);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantBlover);
}

bool PlantBlover::CanBeShoveled()
{
	return false;
}

bool PlantBlover::CanBeTargeted()
{
	return false;
}

void PlantBlover::TakeSmashAttack(ZombiePtr i_srcZombie)
{
}
