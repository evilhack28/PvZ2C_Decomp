//
//  PlantAnimRig_Sunflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_Sunflower.h"

PlantAnimRig_Sunflower::PlantAnimRig_Sunflower()
{
}

PlantAnimRig_Sunflower::~PlantAnimRig_Sunflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Sunflower);

void PlantAnimRig_Sunflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Sunflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Sunflower);
}
