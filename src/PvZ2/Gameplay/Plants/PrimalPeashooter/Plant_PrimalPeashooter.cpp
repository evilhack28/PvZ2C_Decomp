//
//  Plant_PrimalPeashooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PrimalPeashooter.h"

PlantPrimalPeashooter::PlantPrimalPeashooter()
{
}

PlantPrimalPeashooter::~PlantPrimalPeashooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPrimalPeashooter);

void PlantPrimalPeashooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPrimalPeashooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

	REFLECTION_CLASSBUILDER_END(PlantPrimalPeashooter);
}

#include "PlantFramework.h"
void PlantPrimalPeashooter::CancelPlantfood()
{
	 PlantFramework::CancelPlantfood();
}
