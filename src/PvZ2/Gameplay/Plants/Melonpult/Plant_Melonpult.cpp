//
//  Plant_Melonpult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Melonpult.h"

PlantMelonpult::PlantMelonpult()
{
}

PlantMelonpult::~PlantMelonpult()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantMelonpult);

void PlantMelonpult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantMelonpult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<BoardEntity> >, m_targettedBoardEntities);
		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_timesSpecialFired);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_level5);
	REFLECTION_CLASSBUILDER_END(PlantMelonpult);
}

bool PlantMelonpult::CanApplyPlantfood()
{
	return true;
}
