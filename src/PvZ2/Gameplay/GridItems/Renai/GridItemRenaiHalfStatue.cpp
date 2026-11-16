//
//  GridItemRenaiHalfStatue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemRenaiStatue.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

GridItemRenaiHalfStatueProps::~GridItemRenaiHalfStatueProps()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(GridItemRenaiHalfStatueProps);

void GridItemRenaiHalfStatueProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRenaiHalfStatueProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemRenaiStatueProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, ZombiePopAnim);
	REFLECTION_CLASSBUILDER_END(GridItemRenaiHalfStatueProps);
}
