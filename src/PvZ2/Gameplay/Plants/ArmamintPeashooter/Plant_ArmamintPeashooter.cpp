//
//  Plant_ArmamintPeashooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ArmamintPeashooter.h"

PlantArmamintPeashooter::PlantArmamintPeashooter()
{
}

PlantArmamintPeashooter::~PlantArmamintPeashooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantArmamintPeashooter);

void PlantArmamintPeashooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantArmamintPeashooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantArmamintPeashooter);
}

bool PlantArmamintPeashooter::CanApplyPlantfood()
{
	return true;
}
