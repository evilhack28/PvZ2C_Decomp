//
//  PlantAnimRig_PrimalPeashooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PrimalPeashooter.h"

PlantAnimRig_PrimalPeashooter::PlantAnimRig_PrimalPeashooter()
{
}

PlantAnimRig_PrimalPeashooter::~PlantAnimRig_PrimalPeashooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_PrimalPeashooter);

void PlantAnimRig_PrimalPeashooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_PrimalPeashooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_PrimalPeashooter);
}
