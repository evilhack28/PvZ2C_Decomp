//
//  GridItemFrost.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Zombie_IceYearMonster.h"

GridItemFrost::~GridItemFrost()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFrost);

void GridItemFrost::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFrost);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemFrost);
}
