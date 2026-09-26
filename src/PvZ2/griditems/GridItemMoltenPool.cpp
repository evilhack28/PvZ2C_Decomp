//
//  GridItemMoltenPool.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_MeteorFlower.h"

GridItemMoltenPool::GridItemMoltenPool()
{
}

GridItemMoltenPool::~GridItemMoltenPool()
{
}

GridItemMoltenPoolProps::GridItemMoltenPoolProps()
{
}

GridItemMoltenPoolProps::~GridItemMoltenPoolProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMoltenPool);

void GridItemMoltenPool::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMoltenPool);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemLava);

	REFLECTION_CLASSBUILDER_END(GridItemMoltenPool);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMoltenPoolProps);

void GridItemMoltenPoolProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMoltenPoolProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemLavaProps);

	REFLECTION_CLASSBUILDER_END(GridItemMoltenPoolProps);
}
