//
//  GridItemSliderTileAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSliderTile.h"

GridItemSliderTileAnimRig::GridItemSliderTileAnimRig()
{
}

GridItemSliderTileAnimRig::~GridItemSliderTileAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSliderTileAnimRig);

void GridItemSliderTileAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSliderTileAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemSliderTileAnimRig);
}
