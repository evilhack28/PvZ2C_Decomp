//
//  Plant_ElectricPeashooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ElectricPeashooter.h"

PlantElectricPeashooter::PlantElectricPeashooter()
{
}

PlantElectricPeashooter::~PlantElectricPeashooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantElectricPeashooter);

void PlantElectricPeashooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantElectricPeashooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantElectricPeashooter);
}

bool PlantElectricPeashooter::CanApplyPlantfood()
{
	return true;
}
