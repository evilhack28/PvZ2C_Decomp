//
//  GridItemShadowVanillaWhirlpool.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_ShadowVanilla.h"

GridItemShadowVanillaWhirlpool::~GridItemShadowVanillaWhirlpool()
{
}

GridItemShadowVanillaWhirlpoolProps::~GridItemShadowVanillaWhirlpoolProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemShadowVanillaWhirlpool);

void GridItemShadowVanillaWhirlpool::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemShadowVanillaWhirlpool);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, _startTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, _playEndAnim);
	REFLECTION_CLASSBUILDER_END(GridItemShadowVanillaWhirlpool);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemShadowVanillaWhirlpoolProps);

void GridItemShadowVanillaWhirlpoolProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemShadowVanillaWhirlpoolProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<SexyVector2>, WhirlPoolParams);
	REFLECTION_CLASSBUILDER_END(GridItemShadowVanillaWhirlpoolProps);
}
