//
//  Plant_Pitaya.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Pitaya.h"

PlantPitaya::PlantPitaya()
{
	m_timesSpecialFired = 0;
}

PlantPitaya::~PlantPitaya()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPitaya);

void PlantPitaya::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPitaya);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_targettedBoardEntities);
		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_timesSpecialFired);
	REFLECTION_CLASSBUILDER_END(PlantPitaya);
}

bool PlantPitaya::CanApplyPlantfood()
{
	return true;
}
