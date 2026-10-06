//
//  WorldMap_AdsLotteryButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_AdsLotteryButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_AdsLotteryButton);

void WorldMap_AdsLotteryButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_AdsLotteryButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_AdsLotteryButton);
}

#include "WorldMap_AdsLotteryButton.h"
void WorldMap_AdsLotteryButton::onEASquaredAdsAvailableChanged()
{
	 WorldMap_AdsLotteryButton::changeAvailable();
}
