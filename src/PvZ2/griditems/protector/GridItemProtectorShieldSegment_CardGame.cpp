//
//  GridItemProtectorShieldSegment_CardGame.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCardGameProtector.h"

GridItemProtectorShieldSegment_CardGame::GridItemProtectorShieldSegment_CardGame()
{
}

GridItemProtectorShieldSegment_CardGame::~GridItemProtectorShieldSegment_CardGame()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemProtectorShieldSegment_CardGame);

void GridItemProtectorShieldSegment_CardGame::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemProtectorShieldSegment_CardGame);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemProtectorShieldSegment);

	REFLECTION_CLASSBUILDER_END(GridItemProtectorShieldSegment_CardGame);
}

void GridItemProtectorShieldSegment_CardGame::onGridItemInitialize()
{
	GridItemProtectorShieldSegment::onGridItemInitialize();
	JoinTeam(TEAM_PLANTS);
}
