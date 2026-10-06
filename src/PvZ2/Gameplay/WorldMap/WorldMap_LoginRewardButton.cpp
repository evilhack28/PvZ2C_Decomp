//
//  WorldMap_LoginRewardButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_LoginRewardButton.h"

void WorldMap_LoginRewardButton::initLoadingResourcesGroupList()
{
}

void WorldMap_LoginRewardButton::onUpdate()
{
}

WorldMap_LoginRewardButton::WorldMap_LoginRewardButton()
{
}

WorldMap_LoginRewardButton::~WorldMap_LoginRewardButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_LoginRewardButton);

void WorldMap_LoginRewardButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_LoginRewardButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_LoginRewardButton);
}
