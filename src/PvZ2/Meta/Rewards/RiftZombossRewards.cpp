//
//  RiftZombossRewards.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RiftZombossRewards.h"

RiftZombossRewards::~RiftZombossRewards()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftZombossRewards);

void RiftZombossRewards::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftZombossRewardDifficultyEntry);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<LevelOfTheDay_RewardItemType>, Rewards);
	REFLECTION_CLASSBUILDER_END(RiftZombossRewardDifficultyEntry);

	REFLECTION_CLASSBUILDER_BEGIN(RiftZombossRewardDifficultySet);
		REFLECTION_CLASSBUILDER_FIELD(int, Attempt);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RiftZombossRewardDifficultyEntry>, DifficultyList);
	REFLECTION_CLASSBUILDER_END(RiftZombossRewardDifficultySet);

	REFLECTION_CLASSBUILDER_BEGIN(RiftZombossRewards);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PinataTypeForOpeningSequence);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RiftZombossRewardDifficultySet>, ProgressionRewards);
	REFLECTION_CLASSBUILDER_END(RiftZombossRewards);
}
