//
//  GridItemSteamCoal.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSteamCoalMiner.h"

GridItemSteamCoalProps::~GridItemSteamCoalProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemSteamCoalProps);

void GridItemSteamCoalProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemSteamCoalProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimationProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, PopAnimRenderOffset);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Lifetime);
	REFLECTION_CLASSBUILDER_END(GridItemSteamCoalProps);
}
