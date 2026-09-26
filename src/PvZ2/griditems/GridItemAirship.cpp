//
//  GridItemAirship.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemAirship.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemAirship);

void GridItemAirship::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemAirship);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

	REFLECTION_CLASSBUILDER_END(GridItemAirship);
}

void GridItemAirship::onDraw(Sexy::Graphics* i_arg)
{
}
