//
//  Plant_Elaeocarpus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Elaeocarpus.h"

PlantElaeocarpus::PlantElaeocarpus()
{
}

PlantElaeocarpus::~PlantElaeocarpus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantElaeocarpus);

void PlantElaeocarpus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantElaeocarpus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_plantfoodTime);
	REFLECTION_CLASSBUILDER_END(PlantElaeocarpus);
}

bool PlantElaeocarpus::CanApplyPlantfood()
{
	return true;
}

void PlantElaeocarpus::DoSpecial(int i_extraParam)
{
}
