//
//  Plant_Marigold.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Marigold.h"

PlantMarigold::PlantMarigold()
{
}

PlantMarigold::~PlantMarigold()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantMarigold);

void PlantMarigold::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantMarigold);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantMarigold);
}

bool PlantMarigold::CanApplyPlantfood()
{
	return true;
}
