//
//  WorldMap_AnniversaryButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_AnniversaryButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_AnniversaryButton);

void WorldMap_AnniversaryButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_AnniversaryButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_AnniversaryButton);
}

#include "WorldMap_AnniversaryButton.h"
void WorldMap_AnniversaryButton::onWorldLoaded()
{
	 WorldMap_AnniversaryButton::CheckActivated();
}
