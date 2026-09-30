//
//  GridItemSummerFireworks.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSummerFireworks.h"

GridItemSummerFireworks::~GridItemSummerFireworks()
{
}

GridItemSummerFireworksProps::~GridItemSummerFireworksProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSummerFireworks);

void GridItemSummerFireworks::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSummerFireworks);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemSummerFireworks);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSummerFireworksProps);

void GridItemSummerFireworksProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSummerFireworksProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, CanFiredByZombieTypes);
	REFLECTION_CLASSBUILDER_END(GridItemSummerFireworksProps);
}

void GridItemSummerFireworks::updateState()
{
}

bool GridItemSummerFireworks::OverrideProjectileCollision(Projectile* i_arg)
{
	return false;
}

bool GridItemSummerFireworks::CollidesWithType(const CollisionTypeFlags i_arg) const
{
	return true;
}
