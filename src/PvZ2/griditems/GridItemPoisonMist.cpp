//
//  GridItemPoisonMist.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePerfumer.h"

GridItemPoisonMistProps::~GridItemPoisonMistProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPoisonMist);

void GridItemPoisonMist::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPoisonMist);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, _state);
		REFLECTION_CLASSBUILDER_FIELD(Sexy::Point, _position);
	REFLECTION_CLASSBUILDER_END(GridItemPoisonMist);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPoisonMistProps);

void GridItemPoisonMistProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPoisonMistProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, _aliveTimeThreshold);
		REFLECTION_CLASSBUILDER_FIELD(float, _percentOfMaxHealth);
	REFLECTION_CLASSBUILDER_END(GridItemPoisonMistProps);
}
