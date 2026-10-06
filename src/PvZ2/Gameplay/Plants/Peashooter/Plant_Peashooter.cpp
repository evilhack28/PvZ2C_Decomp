//
//  Plant_Peashooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Peashooter.h"

PlantPeashooter::PlantPeashooter()
{
}

PlantPeashooter::~PlantPeashooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPeashooter);

void PlantPeashooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PeashooterPlantfood);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_backwardsProjectiles);
	REFLECTION_CLASSBUILDER_END(PeashooterPlantfood);

	REFLECTION_CLASSBUILDER_BEGIN(PlantPeashooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(PeashooterPlantfood, m_plantfood);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_comboCount);
		REFLECTION_CLASSBUILDER_FIELD(float, m_reShootRate);
	REFLECTION_CLASSBUILDER_END(PlantPeashooter);
}

bool PlantPeashooter::CanApplyPlantfood()
{
	return true;
}
