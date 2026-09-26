//
//  GridItemZombieGasSmoke.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieExplosionProofPolice.h"

GridItemZombieGasSmoke::GridItemZombieGasSmoke()
{
}

GridItemZombieGasSmoke::~GridItemZombieGasSmoke()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombieGasSmoke);

void GridItemZombieGasSmoke::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombieGasSmoke);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPlantConditionTarget);

	REFLECTION_CLASSBUILDER_END(GridItemZombieGasSmoke);
}

bool GridItemZombieGasSmoke::IsDamageable() const
{
	return false;
}

bool GridItemZombieGasSmoke::IsDamageableByPlants() const
{
	return false;
}

void GridItemZombieGasSmoke::DestroySmoke()
{
	 GridItemBreakableTarget::startDeathAnim();
}

bool GridItemZombieGasSmoke::CollidesWithType(CollisionTypeFlags i_collisionTypes) const
{
	return false;
}
