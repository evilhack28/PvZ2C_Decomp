//
//  Plant_BloomingHearts.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BloomingHearts.h"

PlantBloomingHearts::PlantBloomingHearts()
{
}

PlantBloomingHearts::~PlantBloomingHearts()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBloomingHearts);

void PlantBloomingHearts::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBloomingHearts);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_targetedBoardEntities);
		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_timesSpecialFired);
	REFLECTION_CLASSBUILDER_END(PlantBloomingHearts);
}

bool PlantBloomingHearts::CanApplyPlantfood()
{
	return true;
}
