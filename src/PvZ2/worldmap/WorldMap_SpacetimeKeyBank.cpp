//
//  WorldMap_SpacetimeKeyBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_SpacetimeKeyBank.h"

WorldMap_SpacetimeKeyBank::~WorldMap_SpacetimeKeyBank()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_SpacetimeKeyBank);

void WorldMap_SpacetimeKeyBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WorldMap_SpacetimeKeyBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_FIELD(UISpacetimeKeyInfoButton*, m_button);

	REFLECTION_CLASSBUILDER_END(WorldMap_SpacetimeKeyBank);
}
