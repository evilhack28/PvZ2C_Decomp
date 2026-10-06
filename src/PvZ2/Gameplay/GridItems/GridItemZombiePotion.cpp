//
//  GridItemZombiePotion.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemZombiePotion.h"

GridItemZombiePotion::GridItemZombiePotion()
{
	m_spawned = 0;
}

GridItemZombiePotion::~GridItemZombiePotion()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemZombiePotion);

void GridItemZombiePotion::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemZombiePotion);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_spawned);
	REFLECTION_CLASSBUILDER_END(GridItemZombiePotion);
}
