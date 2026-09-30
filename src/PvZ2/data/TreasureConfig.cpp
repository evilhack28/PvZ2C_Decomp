//
//  TreasureConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "TreasureConfig.h"

TreasureConfig::TreasureConfig()
{
}

TreasureConfig::~TreasureConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(TreasureConfig);

void TreasureConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TreasureReward);
	REFLECTION_CLASSBUILDER_END(TreasureReward);

	REFLECTION_CLASSBUILDER_BEGIN(TreasurePool);
	REFLECTION_CLASSBUILDER_END(TreasurePool);

	REFLECTION_CLASSBUILDER_BEGIN(TreasureConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<TreasureReward>, TreasureRewardList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TreasurePool>, TreasurePools);
	REFLECTION_CLASSBUILDER_END(TreasureConfig);
}
