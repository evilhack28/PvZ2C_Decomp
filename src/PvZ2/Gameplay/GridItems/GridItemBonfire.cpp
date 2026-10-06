//
//  GridItemBonfire.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "KongmingLantern.h"

GridItemBonfire::GridItemBonfire()
{
}

GridItemBonfire::~GridItemBonfire()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBonfire);

void GridItemBonfire::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBonfire);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, loopTime);

	REFLECTION_CLASSBUILDER_END(GridItemBonfire);
}
