//
//  Plant_Bearberry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Bearberry.h"

PlantBearberry::PlantBearberry()
{
}

PlantBearberry::~PlantBearberry()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBearberry);

void PlantBearberry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBearberry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantBearberry);
}

void PlantBearberry::UpdateActions()
{
}

#include "PlantFramework.h"
void PlantBearberry::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

bool PlantBearberry::CanApplyPlantfood()
{
	return true;
}
