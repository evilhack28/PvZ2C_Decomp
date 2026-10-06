//
//  GridItemRestrictionSet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RestrictionSet.h"

GridItemRestrictionSet::~GridItemRestrictionSet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRestrictionSet);

void GridItemRestrictionSet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRestrictionSet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StringRestrictionSet);

	REFLECTION_CLASSBUILDER_END(GridItemRestrictionSet);
}
