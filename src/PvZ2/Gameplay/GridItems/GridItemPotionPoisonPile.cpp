//
//  GridItemPotionPoisonPile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombiePotion.h"

GridItemPotionPoisonPile::~GridItemPotionPoisonPile()
{
}

GridItemPotionPoisonPileProps::~GridItemPotionPoisonPileProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPotionPoisonPile);

void GridItemPotionPoisonPile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPotionPoisonPile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
	REFLECTION_CLASSBUILDER_END(GridItemPotionPoisonPile);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemPotionPoisonPileProps);

void GridItemPotionPoisonPileProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemPotionPoisonPileProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
	REFLECTION_CLASSBUILDER_END(GridItemPotionPoisonPileProps);
}
