//
//  Plant_Cabbagepult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cabbagepult.h"

PlantCabbagepult::PlantCabbagepult()
{
}

PlantCabbagepult::~PlantCabbagepult()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCabbagepult);

void PlantCabbagepult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCabbagepult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantCabbagepult);
}

bool PlantCabbagepult::CanApplyPlantfood()
{
	return true;
}
