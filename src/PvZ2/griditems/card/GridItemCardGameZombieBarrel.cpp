//
//  GridItemCardGameZombieBarrel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombieBarrel.h"

GridItemCardGameZombieBarrel::GridItemCardGameZombieBarrel()
{
}

GridItemCardGameZombieBarrel::~GridItemCardGameZombieBarrel()
{
}

GridItemCardGameZombieBarrelProps::GridItemCardGameZombieBarrelProps()
{
	ZombieBarrelCountMax = (decltype(ZombieBarrelCountMax))2;
	ExplodeBarrelCountMax = 1;
}

GridItemCardGameZombieBarrelProps::~GridItemCardGameZombieBarrelProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieBarrel);

void GridItemCardGameZombieBarrel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieBarrel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombie);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieBarrel);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieBarrelProps);

void GridItemCardGameZombieBarrelProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieBarrelProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombieProps);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieBarrelProps);
}
