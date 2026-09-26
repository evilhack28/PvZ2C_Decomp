//
//  PlantAnimRig_GhostPepper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_GhostPepper.h"

PlantAnimRig_GhostPepper::PlantAnimRig_GhostPepper()
{
}

PlantAnimRig_GhostPepper::~PlantAnimRig_GhostPepper()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_GhostPepper);

void PlantAnimRig_GhostPepper::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_GhostPepper);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_GhostPepper);
}
