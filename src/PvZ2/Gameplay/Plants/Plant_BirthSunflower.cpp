//
//  Plant_BirthSunflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BirthSunflower.h"

PlantBirthSunflower::PlantBirthSunflower()
{
}

PlantBirthSunflower::~PlantBirthSunflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBirthSunflower);

void PlantBirthSunflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBirthSunflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantBirthSunflower);
}

#include "PlantFramework.h"
void PlantBirthSunflower::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantBirthSunflower::CanApplyPlantfood()
{
	return true;
}
