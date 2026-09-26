//
//  PlantAnimRig_Rapeflower.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Rapeflower.h"

PlantAnimRig_Rapeflower::~PlantAnimRig_Rapeflower()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Rapeflower);

void PlantAnimRig_Rapeflower::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Rapeflower);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_FIELD(int, attacktypr);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Rapeflower);
}
