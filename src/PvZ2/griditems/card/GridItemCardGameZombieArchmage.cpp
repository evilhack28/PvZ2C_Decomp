//
//  GridItemCardGameZombieArchmage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombieArchmage.h"

GridItemCardGameZombieArchmage::GridItemCardGameZombieArchmage()
{
}

GridItemCardGameZombieArchmage::~GridItemCardGameZombieArchmage()
{
}

GridItemCardGameZombieArchmageProps::~GridItemCardGameZombieArchmageProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieArchmage);

void GridItemCardGameZombieArchmage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieArchmage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombie);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieArchmage);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieArchmageProps);

void GridItemCardGameZombieArchmageProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieArchmageProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombieProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, SummonZombieType);
	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieArchmageProps);
}
