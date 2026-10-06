//
//  GridItemCoalSteamZomboss.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_Steam.h"

GridItemCoalSteamZomboss::~GridItemCoalSteamZomboss()
{
}

GridItemCoalSteamZombossProps::~GridItemCoalSteamZombossProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCoalSteamZomboss);

void GridItemCoalSteamZomboss::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCoalSteamZomboss);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemCoalSteam);

		REFLECTION_CLASSBUILDER_FIELD(int, m_deathType);
		REFLECTION_CLASSBUILDER_FIELD(DamageInfo, m_lastDamageInfo);
	REFLECTION_CLASSBUILDER_END(GridItemCoalSteamZomboss);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemCoalSteamZombossProps);

void GridItemCoalSteamZombossProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemCoalSteamZombossProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemSteamCoalProps);

	REFLECTION_CLASSBUILDER_END(GridItemCoalSteamZombossProps);
}
