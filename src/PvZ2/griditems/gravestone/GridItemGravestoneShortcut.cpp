//
//  GridItemGravestoneShortcut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestoneShortcut.h"

GridItemGravestoneShortcut::GridItemGravestoneShortcut()
{
}

GridItemGravestoneShortcut::~GridItemGravestoneShortcut()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemGravestoneShortcut);

void GridItemGravestoneShortcut::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemGravestoneShortcut);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemGravestone);

	REFLECTION_CLASSBUILDER_END(GridItemGravestoneShortcut);
}
