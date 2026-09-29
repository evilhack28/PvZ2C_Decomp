//
//  Plant_Akee.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Akee.h"

PlantAkee::PlantAkee()
{
}

PlantAkee::~PlantAkee()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAkee);

void PlantAkee::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAkee);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantAkee);
}

bool PlantAkee::CanApplyPlantfood()
{
	return true;
}
