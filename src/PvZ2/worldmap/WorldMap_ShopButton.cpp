//
//  WorldMap_ShopButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_ShopButton.h"

void WorldMap_ShopButton::CheckTutorialAndCancel()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_ShopButton);

void WorldMap_ShopButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_ShopButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_ShopButton);
}
