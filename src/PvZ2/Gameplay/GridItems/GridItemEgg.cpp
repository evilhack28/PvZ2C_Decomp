//
//  GridItemEgg.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemEgg.h"

GridItemEgg::~GridItemEgg()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemEgg);

void GridItemEgg::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemEgg);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(float, m_rotation);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_playingSpecialAnim);
	REFLECTION_CLASSBUILDER_END(GridItemEgg);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemEggProps);

void GridItemEggProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemEggProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, DinoTypeToSpawn);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, FlyDuration);
	REFLECTION_CLASSBUILDER_END(GridItemEggProps);
}

PlantingReason GridItemEgg::GetCantPlantReason() const
{
	return PLANTING_NOT_ON_DINOEGG;
}
