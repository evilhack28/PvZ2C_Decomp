//
//  GridItemCardGameZombieChickenFarmer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombieChickenFarmer.h"

GridItemCardGameZombieChickenFarmer::GridItemCardGameZombieChickenFarmer()
{
}

GridItemCardGameZombieChickenFarmer::~GridItemCardGameZombieChickenFarmer()
{
}

GridItemCardGameZombieChickenFarmerProps::~GridItemCardGameZombieChickenFarmerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieChickenFarmer);

void GridItemCardGameZombieChickenFarmer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieChickenFarmer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombie);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieChickenFarmer);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieChickenFarmerProps);

void GridItemCardGameZombieChickenFarmerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieChickenFarmerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombieProps);

		REFLECTION_CLASSBUILDER_FIELD(Sexy::Rect, SpawnGraveyardRect);
	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieChickenFarmerProps);
}

#include "GridItemCardGameZombie.h"
void GridItemCardGameZombieChickenFarmer::onUpdate()
{
	 GridItemCardGameZombie::onUpdate();
}
