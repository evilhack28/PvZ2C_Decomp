//
//  PlantAnimRig_BirthSunflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_BirthSunflower.h"

PlantAnimRig_BirthSunflower::PlantAnimRig_BirthSunflower()
{
}

PlantAnimRig_BirthSunflower::~PlantAnimRig_BirthSunflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_BirthSunflower);

void PlantAnimRig_BirthSunflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_BirthSunflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_BirthSunflower);
}
