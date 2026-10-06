//
//  WorldMap_SpacetimeStarBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_SpacetimeStarBank.h"

WorldMap_SpacetimeStarBank::~WorldMap_SpacetimeStarBank()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_SpacetimeStarBank);

void WorldMap_SpacetimeStarBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_SpacetimeStarBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_FIELD(UISpacetimeStarRewardButton*, m_button);

	REFLECTION_CLASSBUILDER_END(WorldMap_SpacetimeStarBank);
}
