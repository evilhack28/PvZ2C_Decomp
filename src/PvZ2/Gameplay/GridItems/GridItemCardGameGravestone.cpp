//
//  GridItemCardGameGravestone.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemGravestoneZombieInCardGame.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

GridItemCardGameGravestonePropertySheet::GridItemCardGameGravestonePropertySheet()
{
}

GridItemCardGameGravestonePropertySheet::~GridItemCardGameGravestonePropertySheet()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(GridItemCardGameGravestonePropertySheet);

void GridItemCardGameGravestonePropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCardGameGravestonePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(int, AdvanceTimes);
		REFLECTION_CLASSBUILDER_FIELD(float, Cooldown);
	REFLECTION_CLASSBUILDER_END(GridItemCardGameGravestonePropertySheet);
}
