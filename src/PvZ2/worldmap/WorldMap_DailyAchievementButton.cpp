//
//  WorldMap_DailyAchievementButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_DailyAchievementButton.h"

void WorldMap_DailyAchievementButton::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_DailyAchievementButton);

void WorldMap_DailyAchievementButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_DailyAchievementButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_DailyAchievementButton);
}

#include "WorldMap_DailyAchievementButton.h"
void WorldMap_DailyAchievementButton::onNotifyAchievementConfigChanged()
{
	 WorldMap_DailyAchievementButton::CheckActivited();
}
