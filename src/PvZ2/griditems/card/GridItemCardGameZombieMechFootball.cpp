//
//  GridItemCardGameZombieMechFootball.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombieMechFootball.h"

GridItemCardGameZombieMechFootball::GridItemCardGameZombieMechFootball()
{
	m_initHalfBloodAction = 0;
	m_isHalfBloodAction = 0;
}

GridItemCardGameZombieMechFootball::~GridItemCardGameZombieMechFootball()
{
}

GridItemCardGameZombieMechFootballProps::~GridItemCardGameZombieMechFootballProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieMechFootball);

void GridItemCardGameZombieMechFootball::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieMechFootball);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombie);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieMechFootball);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCardGameZombieMechFootballProps);

void GridItemCardGameZombieMechFootballProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameZombieMechFootballProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCardGameZombieProps);

	REFLECTION_CLASSBUILDER_END(GridItemCardGameZombieMechFootballProps);
}
