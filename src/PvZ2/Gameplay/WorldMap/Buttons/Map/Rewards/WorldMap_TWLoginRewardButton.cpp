//
//  WorldMap_TWLoginRewardButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_TWLoginRewardButton.h"

bool WorldMap_TWLoginRewardButton::ShowTheNotice()
{
	return false;
}

void WorldMap_TWLoginRewardButton::initLoadingResourcesGroupList()
{
}

void WorldMap_TWLoginRewardButton::onUpdate()
{
}

WorldMap_TWLoginRewardButton::WorldMap_TWLoginRewardButton()
{
}

WorldMap_TWLoginRewardButton::~WorldMap_TWLoginRewardButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_TWLoginRewardButton);

void WorldMap_TWLoginRewardButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_TWLoginRewardButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_TWLoginRewardButton);
}
