//
//  Plant_Nightshade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Nightshade.h"

PlantNightshade::PlantNightshade()
{
}

PlantNightshade::~PlantNightshade()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantNightshade);

void PlantNightshade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantNightshade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_currentLeafCount);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_timeToRegenLeaf);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_plantfooded);
	REFLECTION_CLASSBUILDER_END(PlantNightshade);
}

bool PlantNightshade::CanApplyPlantfood()
{
	return true;
}
