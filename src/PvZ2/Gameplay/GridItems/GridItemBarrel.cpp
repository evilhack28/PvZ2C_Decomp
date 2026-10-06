//
//  GridItemBarrel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemBarrel.h"

GridItemBarrel::GridItemBarrel()
{
	m_hasBroken = 0;
}

GridItemBarrel::~GridItemBarrel()
{
}

GridItemBarrelProps::~GridItemBarrelProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBarrel);

void GridItemBarrel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GriditemBarrelZombieDes);
		REFLECTION_CLASSBUILDER_FIELD(int, Level);
		REFLECTION_CLASSBUILDER_FIELD(std::string, TypeName);
	REFLECTION_CLASSBUILDER_END(GriditemBarrelZombieDes);

	REFLECTION_CLASSBUILDER_BEGIN(GriditemBarrelParams);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<GriditemBarrelZombieDes>, Zombies);
	REFLECTION_CLASSBUILDER_END(GriditemBarrelParams);

	REFLECTION_CLASSBUILDER_BEGIN(GridItemBarrel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTarget);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<GriditemBarrelZombieDes>, m_zombies);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasBroken);
	REFLECTION_CLASSBUILDER_END(GridItemBarrel);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemBarrelProps);

void GridItemBarrelProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemBarrelProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBoardEntityConditionTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, SpawnImpLevel);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<GriditemBarrelZombieDes>, Zombies);
	REFLECTION_CLASSBUILDER_END(GridItemBarrelProps);
}
