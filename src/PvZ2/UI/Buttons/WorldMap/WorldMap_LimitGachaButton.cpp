//
//  WorldMap_LimitGachaButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_LimitGachaButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_LimitGachaButton);

void WorldMap_LimitGachaButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_LimitGachaButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_LimitGachaButton);
}

#include "WorldMap_LimitGachaButton.h"
void WorldMap_LimitGachaButton::onWorldLoaded()
{
	 WorldMap_LimitGachaButton::CheckActivated();
}

#include "UILimitedGacha.h"
void WorldMap_LimitGachaButton::onButtonClicked()
{
	 UILimitedGacha::createWithNetwork();
}

void WorldMap_LimitGachaButton::onUpdate()
{
}
