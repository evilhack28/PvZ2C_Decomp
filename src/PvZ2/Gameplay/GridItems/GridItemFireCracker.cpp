//
//  GridItemFireCracker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemFireCracker.h"

GridItemFireCracker::~GridItemFireCracker()
{
}

GridItemFireCrackerProps::~GridItemFireCrackerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFireCracker);

void GridItemFireCracker::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFireCracker);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemFireCracker);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFireCrackerProps);

void GridItemFireCrackerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFireCrackerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, CanFiredByZombieTypes);
	REFLECTION_CLASSBUILDER_END(GridItemFireCrackerProps);
}

void GridItemFireCracker::updateState()
{
}

bool GridItemFireCracker::OverrideProjectileCollision(Projectile* i_projectile)
{
	return false;
}

bool GridItemFireCracker::CollidesWithType(const CollisionTypeFlags i_collisionTypes) const
{
	return true;
}
