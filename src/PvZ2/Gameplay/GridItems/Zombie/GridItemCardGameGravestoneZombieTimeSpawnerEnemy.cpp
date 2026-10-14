//
//  GridItemCardGameGravestoneZombieTimeSpawnerEnemy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestoneZombieInCardGame.h"

GridItemCardGameGravestoneZombieTimeSpawnerEnemy::~GridItemCardGameGravestoneZombieTimeSpawnerEnemy()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameGravestoneZombieTimeSpawnerEnemy);

void GridItemCardGameGravestoneZombieTimeSpawnerEnemy::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameGravestoneZombieTimeSpawnerEnemy);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameGravestoneZombieTimeSpawnerEnemy);
}

#include "GridItem.h"
void GridItemCardGameGravestoneZombieTimeSpawnerEnemy::registerForEvents()
{
	 GridItem::registerForEvents();
}
