//
//  WorldMap_PerkLibraryButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_PerkLibraryButton.h"

void WorldMap_PerkLibraryButton::onLoadComplete()
{
}

WorldMap_PerkLibraryButton::~WorldMap_PerkLibraryButton()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_PerkLibraryButton);

void WorldMap_PerkLibraryButton::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_PerkLibraryButton);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIButtonWidget);

	REFLECTION_CLASSBUILDER_END(WorldMap_PerkLibraryButton);
}
