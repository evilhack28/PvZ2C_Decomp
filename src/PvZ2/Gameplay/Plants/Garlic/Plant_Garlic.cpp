//
//  Plant_Garlic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Garlic.h"

PlantGarlic::PlantGarlic()
{
}

PlantGarlic::~PlantGarlic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGarlic);

void PlantGarlic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGarlic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantGarlic);
}

bool PlantGarlic::CanApplyPlantfood()
{
	return true;
}
