//
//  Plant_ImpPear.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ImpPear.h"

PlantImpPear::PlantImpPear()
{
}

PlantImpPear::~PlantImpPear()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantImpPear);

void PlantImpPear::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantImpPear);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantImpPear);
}

#include "PlantFramework.h"
void PlantImpPear::Initialize()
{
	 PlantFramework::Initialize();
}

bool PlantImpPear::CanApplyPlantfood()
{
	return true;
}
