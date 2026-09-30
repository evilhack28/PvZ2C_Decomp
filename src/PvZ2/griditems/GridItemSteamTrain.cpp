//
//  GridItemSteamTrain.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_Steam.h"

GridItemSteamTrain::~GridItemSteamTrain()
{
}

GridItemSteamTrainProps::~GridItemSteamTrainProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSteamTrain);

void GridItemSteamTrain::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSteamTrain);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_startMovingTime);
	REFLECTION_CLASSBUILDER_END(GridItemSteamTrain);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSteamTrainProps);

void GridItemSteamTrainProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSteamTrainProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(int8, DamageStateCount);
	REFLECTION_CLASSBUILDER_END(GridItemSteamTrainProps);
}

PlantingReason GridItemSteamTrain::GetCantPlantReason() const
{
	return (PlantingReason)97;
}
