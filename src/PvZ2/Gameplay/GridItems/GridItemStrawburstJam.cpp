//
//  GridItemStrawburstJam.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Strawburst.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

GridItemStrawburstJamProps::~GridItemStrawburstJamProps()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(GridItemStrawburstJamProps);

void GridItemStrawburstJamProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemStrawburstJamProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ZombieBlacklist);
	REFLECTION_CLASSBUILDER_END(GridItemStrawburstJamProps);
}
