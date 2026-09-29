//
//  Plant_Flamelady.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Flamelady.h"

PlantFlamelady::~PlantFlamelady()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantFlamelady);

void PlantFlamelady::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EntityTarget);
		REFLECTION_CLASSBUILDER_FIELD(int, row);
		REFLECTION_CLASSBUILDER_FIELD(bool, flameSpawned);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, flameSpawnTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, entity);
	REFLECTION_CLASSBUILDER_END(EntityTarget);

	REFLECTION_CLASSBUILDER_BEGIN(PlantFlamelady);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentWarmingRadius>, m_warmingRadius);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Effect_AngerFlame>>, m_flameEffects);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<EntityTarget>, m_entityTargets);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_attackInterval);
	REFLECTION_CLASSBUILDER_END(PlantFlamelady);
}

bool PlantFlamelady::CanApplyPlantfood()
{
	return true;
}

#include "Plant_Flamelady.h"
void PlantFlamelady::stopSpecialEffect()
{
	 PlantFlamelady::CancelPowerAttack();
}

#include "Plant_Flamelady.h"
void PlantFlamelady::onKilled(bool i_arg)
{
	 PlantFlamelady::CancelPowerAttack();
}
