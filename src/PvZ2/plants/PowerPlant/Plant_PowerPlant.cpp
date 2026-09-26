//
//  Plant_PowerPlant.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PowerPlant.h"

PlantPowerPlant::PlantPowerPlant()
{
}

PlantPowerPlant::~PlantPowerPlant()
{
}

PlantTypePowerPlant::PlantTypePowerPlant()
{
}

PlantTypePowerPlant::~PlantTypePowerPlant()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPowerPlant);

void PlantPowerPlant::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPowerPlant);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_createdTile);

	REFLECTION_CLASSBUILDER_END(PlantPowerPlant);
}

bool PlantPowerPlant::CanBeShoveled()
{
	return false;
}

bool PlantPowerPlant::HasShadow()
{
	return true;
}
