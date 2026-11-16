//
//  Plant_Strawburst.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Strawburst.h"

PlantStrawBurst::~PlantStrawBurst()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantStrawBurst);

void PlantStrawBurst::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantStrawBurst);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_currentGrowthStage);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextGrowthTime);
	REFLECTION_CLASSBUILDER_END(PlantStrawBurst);
}

#include "Plant_Strawburst.h"
void PlantStrawBurst::onGameplayEnded()
{
	 PlantStrawBurst::unregisterTouchesIfNeeded();
}

bool PlantStrawBurst::CanApplyPlantfood()
{
	return true;
}
