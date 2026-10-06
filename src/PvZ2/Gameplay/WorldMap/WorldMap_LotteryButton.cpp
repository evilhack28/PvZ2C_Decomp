//
//  WorldMap_LotteryButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_LotteryButton.h"

void WorldMap_LotteryButton::initLoadingResourcesGroupList()
{
}

void WorldMap_LotteryButton::onUpdate()
{
}

WorldMap_LotteryButton::WorldMap_LotteryButton()
{
}

WorldMap_LotteryButton::~WorldMap_LotteryButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_LotteryButton);

void WorldMap_LotteryButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_LotteryButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_LotteryButton);
}
