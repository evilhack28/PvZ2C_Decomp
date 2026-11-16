//
//  Plant_Bamboo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Bamboo.h"

PlantBamboo::~PlantBamboo()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantBamboo);

void PlantBamboo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantBamboo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(int, m_rangeNum);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_animInterval);
	REFLECTION_CLASSBUILDER_END(PlantBamboo);
}

void PlantBamboo::UpdatePlantfood()
{
}
