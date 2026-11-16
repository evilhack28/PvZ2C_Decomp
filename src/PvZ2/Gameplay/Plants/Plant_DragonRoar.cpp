//
//  Plant_DragonRoar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_DragonRoar.h"

PlantDragonRoar::PlantDragonRoar()
{
	m_isNovaSuccessful = 0;
	m_isNovaDealingDamage = 0;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantDragonRoar);

void PlantDragonRoar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantDragonRoar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_lastState);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_targetEntity);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie> >, m_suctionZombies);
	REFLECTION_CLASSBUILDER_END(PlantDragonRoar);
}

bool PlantDragonRoar::CanApplyPlantfood()
{
	return true;
}
