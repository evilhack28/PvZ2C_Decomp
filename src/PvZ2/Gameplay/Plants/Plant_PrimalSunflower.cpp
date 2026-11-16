//
//  Plant_PrimalSunflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PrimalSunflower.h"

PlantPrimalSunflower::PlantPrimalSunflower()
{
}

PlantPrimalSunflower::~PlantPrimalSunflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantPrimalSunflower);

void PlantPrimalSunflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantPrimalSunflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantSunflower);

	REFLECTION_CLASSBUILDER_END(PlantPrimalSunflower);
}

void PlantPrimalSunflower::onKilled(bool i_instantKill)
{
}
