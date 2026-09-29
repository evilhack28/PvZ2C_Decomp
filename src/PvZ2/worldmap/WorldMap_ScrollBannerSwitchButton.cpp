//
//  WorldMap_ScrollBannerSwitchButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_ScrollBannerSwitchButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_ScrollBannerSwitchButton);

void WorldMap_ScrollBannerSwitchButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_ScrollBannerSwitchButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

		REFLECTION_CLASSBUILDER_FIELD(bool, _isShowing);
	REFLECTION_CLASSBUILDER_END(WorldMap_ScrollBannerSwitchButton);
}
