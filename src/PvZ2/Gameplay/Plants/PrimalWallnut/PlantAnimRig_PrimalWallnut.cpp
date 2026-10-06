//
//  PlantAnimRig_PrimalWallnut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_PrimalWallnut.h"

PlantAnimRig_PrimalWallnut::PlantAnimRig_PrimalWallnut()
{
}

PlantAnimRig_PrimalWallnut::~PlantAnimRig_PrimalWallnut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_PrimalWallnut);

void PlantAnimRig_PrimalWallnut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_PrimalWallnut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig_Wallnut);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_PrimalWallnut);
}
