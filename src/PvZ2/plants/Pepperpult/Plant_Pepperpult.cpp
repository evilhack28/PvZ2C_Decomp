//
//  Plant_Pepperpult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Pepperpult.h"

PlantPepperpult::PlantPepperpult()
{
	m_timesSpecialFired = 0;
}

PlantPepperpult::~PlantPepperpult()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPepperpult);

void PlantPepperpult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPepperpult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ComponentWarmingRadius>, m_warmingRadius);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_targetedBoardEntities);
		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_timesSpecialFired);
	REFLECTION_CLASSBUILDER_END(PlantPepperpult);
}

bool PlantPepperpult::CanApplyPlantfood()
{
	return true;
}

void PlantPepperpult::onKilled(bool i_arg)
{
}
