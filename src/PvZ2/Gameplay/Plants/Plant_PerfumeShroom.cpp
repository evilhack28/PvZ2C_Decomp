//
//  Plant_PerfumeShroom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PerfumeShroom.h"

PlantPerfumeShroom::PlantPerfumeShroom()
{
}

PlantPerfumeShroom::~PlantPerfumeShroom()
{
}

PlantPerfumeShroomProps::~PlantPerfumeShroomProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPerfumeShroom);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPerfumeShroomProps);

void PlantPerfumeShroomProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPerfumeShroomProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(ComponentPropagatedBurstProps, CharmBurstProps);
	REFLECTION_CLASSBUILDER_END(PlantPerfumeShroomProps);
}

bool PlantPerfumeShroom::CanBeShoveled()
{
	return false;
}

bool PlantPerfumeShroom::CanBeTargeted()
{
	return false;
}

void PlantPerfumeShroom::TakeSmashAttack(ZombiePtr i_srcZombie)
{
}
