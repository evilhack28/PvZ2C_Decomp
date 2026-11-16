//
//  GridItemGravestoneZombieTimeSpawner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestoneZombieTimeSpawner.h"

GridItemGravestoneZombieTimeSpawner::~GridItemGravestoneZombieTimeSpawner()
{
}

GridItemGravestoneZombieTimeSpawnerPropertySheet::~GridItemGravestoneZombieTimeSpawnerPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestoneZombieTimeSpawner);

void GridItemGravestoneZombieTimeSpawner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestoneZombieTimeSpawner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_END(GridItemGravestoneZombieTimeSpawner);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestoneZombieTimeSpawnerPropertySheet);

void GridItemGravestoneZombieTimeSpawnerPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestoneZombieTimeSpawnerPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestonePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, ZombieTypeName);
	REFLECTION_CLASSBUILDER_END(GridItemGravestoneZombieTimeSpawnerPropertySheet);
}
