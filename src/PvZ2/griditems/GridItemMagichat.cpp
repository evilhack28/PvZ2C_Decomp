//
//  GridItemMagichat.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCarnieMagician.h"

GridItemMagichat::~GridItemMagichat()
{
}

GridItemMagichatProps::~GridItemMagichatProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemMagichat);

void GridItemMagichat::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemMagichat);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTarget);

	REFLECTION_CLASSBUILDER_FIELD(int, m_currentLevel);

	REFLECTION_CLASSBUILDER_END(GridItemMagichat);
}
