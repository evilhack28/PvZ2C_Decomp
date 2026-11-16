//
//  PlantAnimRig_JewelRabbit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_JewelRabbit.h"

PlantAnimRig_JewelRabbit::PlantAnimRig_JewelRabbit()
{
}

PlantAnimRig_JewelRabbit::~PlantAnimRig_JewelRabbit()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_JewelRabbit);

void PlantAnimRig_JewelRabbit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_JewelRabbit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_JewelRabbit);
}
