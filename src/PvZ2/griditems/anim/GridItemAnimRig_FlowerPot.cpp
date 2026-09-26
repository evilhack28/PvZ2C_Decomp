//
//  GridItemAnimRig_FlowerPot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_FlowerPot.h"

GridItemAnimRig_FlowerPot::GridItemAnimRig_FlowerPot()
{
}

GridItemAnimRig_FlowerPot::~GridItemAnimRig_FlowerPot()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemAnimRig_FlowerPot);

void GridItemAnimRig_FlowerPot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemAnimRig_FlowerPot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemAnimRig_FlowerPot);
}

void GridItemAnimRig_FlowerPot::PlayPlantLeftTile()
{
}
