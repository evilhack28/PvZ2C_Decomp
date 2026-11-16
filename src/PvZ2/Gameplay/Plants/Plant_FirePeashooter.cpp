//
//  Plant_FirePeashooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_FirePeashooter.h"

PlantFirePeashooter::PlantFirePeashooter()
{
}

PlantFirePeashooter::~PlantFirePeashooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantFirePeashooter);

void PlantFirePeashooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantFirePeashooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentWarmingRadius>, m_warmingRadius);
		REFLECTION_CLASSBUILDER_FIELD(int, m_currentFountain);
	REFLECTION_CLASSBUILDER_END(PlantFirePeashooter);
}

bool PlantFirePeashooter::CanApplyPlantfood()
{
	return true;
}

void PlantFirePeashooter::onKilled(bool i_instantKill)
{
}
