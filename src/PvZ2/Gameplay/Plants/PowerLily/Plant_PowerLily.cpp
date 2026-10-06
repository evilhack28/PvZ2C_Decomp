//
//  Plant_PowerLily.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PowerLily.h"

PlantPowerLily::PlantPowerLily()
{
}

PlantPowerLily::~PlantPowerLily()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPowerLily);

void PlantPowerLily::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPowerLily);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_spawningPlantFood);

	REFLECTION_CLASSBUILDER_END(PlantPowerLily);
}

#include "PlantFramework.h"
void PlantPowerLily::ApplyPlantfood()
{
	 PlantFramework::ApplyPlantfood();
}

bool PlantPowerLily::OverrideProjectileCollision(class Projectile* i_arg)
{
	return true;
}
