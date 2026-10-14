//
//  RiftFirstClearRewards.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RiftFirstClearRewards.h"

RiftFirstClearRewards::~RiftFirstClearRewards()
{
}

RiftFirstClearRewardsDefinition::~RiftFirstClearRewardsDefinition()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftFirstClearRewards);

void RiftFirstClearRewards::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftFirstClearRewardsDefinition);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<LevelOfTheDay_RewardItemType>, FirstClearRewards);
	REFLECTION_CLASSBUILDER_END(RiftFirstClearRewardsDefinition);

	REFLECTION_CLASSBUILDER_BEGIN(RiftFirstClearRewards);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<RiftFirstClearRewardsDefinition>, LevelClearRewards);
		REFLECTION_CLASSBUILDER_FIELD(RiftFirstClearRewardsDefinition, DefaultLevelClearRewards);
	REFLECTION_CLASSBUILDER_END(RiftFirstClearRewards);
}
