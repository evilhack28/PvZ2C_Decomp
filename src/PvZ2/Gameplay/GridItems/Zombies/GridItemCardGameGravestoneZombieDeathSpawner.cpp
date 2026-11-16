//
//  GridItemCardGameGravestoneZombieDeathSpawner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestoneZombieInCardGame.h"

GridItemCardGameGravestoneZombieDeathSpawner::~GridItemCardGameGravestoneZombieDeathSpawner()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameGravestoneZombieDeathSpawner);

void GridItemCardGameGravestoneZombieDeathSpawner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameGravestoneZombieDeathSpawner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameGravestoneZombieDeathSpawner);
}

#include "GridItemGravestone.h"
void GridItemCardGameGravestoneZombieDeathSpawner::onUpdate()
{
	 GridItemGravestone::onUpdate();
}
