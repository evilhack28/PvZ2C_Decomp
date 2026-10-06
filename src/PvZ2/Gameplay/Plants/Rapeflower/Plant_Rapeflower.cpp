//
//  Plant_Rapeflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Rapeflower.h"

PlantRapeflower::PlantRapeflower()
{
}

PlantRapeflower::~PlantRapeflower()
{
}

PlantRapeflowerProps::~PlantRapeflowerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantRapeflower);

void PlantRapeflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantRapeflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantRapeflower);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantRapeflowerProps);

void PlantRapeflowerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantRapeflowerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantPropertySheet);

	REFLECTION_CLASSBUILDER_END(PlantRapeflowerProps);
}

#include "PlantFramework.h"
void PlantRapeflower::Initialize()
{
	 PlantFramework::Initialize();
}

#include "PlantFramework.h"
void PlantRapeflower::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}

void PlantRapeflower::UpdatePlantfood()
{
}

bool PlantRapeflower::CanApplyPlantfood()
{
	return true;
}
