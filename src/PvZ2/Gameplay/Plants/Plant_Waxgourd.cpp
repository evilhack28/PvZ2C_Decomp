//
//  Plant_Waxgourd.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Waxgourd.h"

PlantWaxgourd::~PlantWaxgourd()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantWaxgourd);

void PlantWaxgourd::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantWaxgourd);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantWaxgourd);
}

bool PlantWaxgourd::HasGravity()
{
	return true;
}

bool PlantWaxgourd::CanApplyPlantfood()
{
	return true;
}
