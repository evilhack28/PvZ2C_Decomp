//
//  Plant_Sapfling.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Sapfling.h"

PlantSapfling::PlantSapfling()
{
}

PlantSapfling::~PlantSapfling()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantSapfling);

void PlantSapfling::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantSapfling);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantSapfling);
}

bool PlantSapfling::CanApplyPlantfood()
{
	return true;
}
