//
//  PlantAnimRig_CarrotLauncher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig_CarrotLauncher.h"

PlantAnimRig_CarrotLauncher::PlantAnimRig_CarrotLauncher()
{
}

PlantAnimRig_CarrotLauncher::~PlantAnimRig_CarrotLauncher()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_CarrotLauncher);

void PlantAnimRig_CarrotLauncher::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_CarrotLauncher);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_CarrotLauncher);
}
