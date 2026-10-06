//
//  GridItemKongmingLantern.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "KongmingLantern.h"

GridItemKongmingLantern::GridItemKongmingLantern()
{
}

GridItemKongmingLantern::~GridItemKongmingLantern()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemKongmingLantern);

void GridItemKongmingLantern::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemKongmingLantern);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

	REFLECTION_CLASSBUILDER_END(GridItemKongmingLantern);
}
