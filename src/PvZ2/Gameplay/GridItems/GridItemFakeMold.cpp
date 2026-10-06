//
//  GridItemFakeMold.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LevelBasedModifierModule.h"

GridItemFakeMold::GridItemFakeMold()
{
}

GridItemFakeMold::~GridItemFakeMold()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFakeMold);

void GridItemFakeMold::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFakeMold);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemFakeMold);
}

PlantingReason GridItemFakeMold::GetCantPlantReason() const
{
	return (PlantingReason)30;
}
