//
//  Plant_CrownFlower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_CrownFlower.h"

PlantCrownFlower::PlantCrownFlower()
{
}

PlantCrownFlower::~PlantCrownFlower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantCrownFlower);

void PlantCrownFlower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCrownFlower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_target);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isInHighEnergyState);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PenetratingRayEntity>, m_rayEntity);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie>>, m_pushingZombies);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_firePosition);
	REFLECTION_CLASSBUILDER_END(PlantCrownFlower);
}

#include "PlantFramework.h"
void PlantCrownFlower::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantCrownFlower::CanApplyPlantfood()
{
	return true;
}
