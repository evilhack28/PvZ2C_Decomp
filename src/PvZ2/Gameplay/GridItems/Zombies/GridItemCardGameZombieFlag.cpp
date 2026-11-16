//
//  GridItemCardGameZombieFlag.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombieFlag.h"

GridItemCardGameZombieFlag::GridItemCardGameZombieFlag()
{
	m_summonCount = 1;
	m_summonCountMax = 1;
}

GridItemCardGameZombieFlag::~GridItemCardGameZombieFlag()
{
}

GridItemCardGameZombieFlagProps::~GridItemCardGameZombieFlagProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieFlag);

void GridItemCardGameZombieFlag::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieFlag);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombie);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieFlag);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieFlagProps);

void GridItemCardGameZombieFlagProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieFlagProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombieProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, SummonZombies);
	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieFlagProps);
}
