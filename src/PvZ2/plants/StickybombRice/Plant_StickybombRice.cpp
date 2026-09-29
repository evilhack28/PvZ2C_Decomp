//
//  Plant_StickybombRice.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_StickybombRice.h"

PlantStickybombRice::PlantStickybombRice()
{
}

PlantStickybombRice::~PlantStickybombRice()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantStickybombRice);

void PlantStickybombRice::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantStickybombRice);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantStickybombRice);
}

bool PlantStickybombRice::CanApplyPlantfood()
{
	return true;
}
