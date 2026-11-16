//
//  WorldMap_CommonButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_CommonButton.h"

bool WorldMap_CommonButton::IsNeedTips()
{
	return false;
}

void WorldMap_CommonButton::initLoadingResourcesGroupList()
{
}

void WorldMap_CommonButton::onUpdate()
{
}

WorldMap_CommonButton::~WorldMap_CommonButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_CommonButton);

void WorldMap_CommonButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_CommonButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_CommonButton);
}
