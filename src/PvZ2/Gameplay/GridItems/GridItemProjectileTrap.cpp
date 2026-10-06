//
//  GridItemProjectileTrap.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemProjectileTrap.h"

GridItemProjectileTrap::GridItemProjectileTrap()
{
	m_currentState = 1;
}

GridItemProjectileTrap::~GridItemProjectileTrap()
{
}

GridItemProjectileTrapProps::~GridItemProjectileTrapProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemProjectileTrap);

void GridItemProjectileTrap::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemProjectileTrap);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemTriggerTile);

		REFLECTION_CLASSBUILDER_FIELD(int32_t, m_currentState);
	REFLECTION_CLASSBUILDER_END(GridItemProjectileTrap);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemProjectileTrapProps);
