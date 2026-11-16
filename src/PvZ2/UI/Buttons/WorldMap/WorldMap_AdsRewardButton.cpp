//
//  WorldMap_AdsRewardButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_AdsRewardButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_AdsRewardButton);

void WorldMap_AdsRewardButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_AdsRewardButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_AdsRewardButton);
}

#include "WorldMap_AdsRewardButton.h"
void WorldMap_AdsRewardButton::onEASquaredAdsAvailableChanged()
{
	 WorldMap_AdsRewardButton::changeAvailable();
}
