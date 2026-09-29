//
//  WorldMap_RechargeReward.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_RechargeReward.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_RechargeReward);

void WorldMap_RechargeReward::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_RechargeReward);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_RechargeReward);
}

#include "WorldMap_RechargeReward.h"
void WorldMap_RechargeReward::onWorldLoaded()
{
	 WorldMap_RechargeReward::CheckActivated();
}

void WorldMap_RechargeReward::onUpdate()
{
}
