//
//  Plant_DragonCane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_DragonCane.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDragonCane);

void PlantDragonCane::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDragonCane);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantDragonCane);
}

bool PlantDragonCane::CanApplyPlantfood()
{
	return true;
}
