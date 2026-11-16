//
//  WorldMap_DaveClubButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_DaveClubButton.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_DaveClubButton);

void WorldMap_DaveClubButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_DaveClubButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIEasyButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_DaveClubButton);
}

#include "WorldMap_DaveClubButton.h"
void WorldMap_DaveClubButton::onWorldLoaded()
{
	 WorldMap_DaveClubButton::CheckActivated();
}
