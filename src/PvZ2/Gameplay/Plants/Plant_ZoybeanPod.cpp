//
//  Plant_ZoybeanPod.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ZoybeanPod.h"

PlantZoybeanPod::PlantZoybeanPod()
{
	displayN = 0;
	displaySpwan = 0;
}

PlantZoybeanPod::~PlantZoybeanPod()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantZoybeanPod);

void PlantZoybeanPod::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantZoybeanPod);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantZoybeanPod);
}

bool PlantZoybeanPod::CanApplyPlantfood()
{
	return true;
}
