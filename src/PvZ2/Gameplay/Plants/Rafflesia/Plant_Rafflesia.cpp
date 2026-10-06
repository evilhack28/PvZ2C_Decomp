//
//  Plant_Rafflesia.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Rafflesia.h"

PlantRafflesia::PlantRafflesia()
{
}

PlantRafflesia::~PlantRafflesia()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantRafflesia);

void PlantRafflesia::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantRafflesia);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantRafflesia);
}

#include "PlantFramework.h"
void PlantRafflesia::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

bool PlantRafflesia::CanApplyPlantfood()
{
	return true;
}
