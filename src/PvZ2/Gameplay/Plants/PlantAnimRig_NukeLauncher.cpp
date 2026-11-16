//
//  PlantAnimRig_NukeLauncher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_NukeLauncher.h"

PlantAnimRig_NukeLauncher::PlantAnimRig_NukeLauncher()
{
}

PlantAnimRig_NukeLauncher::~PlantAnimRig_NukeLauncher()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_NukeLauncher);

void PlantAnimRig_NukeLauncher::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_NukeLauncher);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_NukeLauncher);
}
