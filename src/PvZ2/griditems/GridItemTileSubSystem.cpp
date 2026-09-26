//
//  GridItemTileSubSystem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemTileSubSystem.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemTileSubSystem);

void GridItemTileSubSystem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemTileSubSystem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameSubSystem);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<Sexy::Point>, _gridItemPositionContainer);

	REFLECTION_CLASSBUILDER_END(GridItemTileSubSystem);
}
