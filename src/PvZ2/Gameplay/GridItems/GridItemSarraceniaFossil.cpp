//
//  GridItemSarraceniaFossil.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSarraceniaFossil.h"

GridItemSarraceniaFossil::GridItemSarraceniaFossil()
{
}

GridItemSarraceniaFossil::~GridItemSarraceniaFossil()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSarraceniaFossil);

void GridItemSarraceniaFossil::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSarraceniaFossil);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

		REFLECTION_CLASSBUILDER_FIELD(float, m_stoneHitpoints);
	REFLECTION_CLASSBUILDER_END(GridItemSarraceniaFossil);
}
