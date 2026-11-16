//
//  ArenaStarBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArenaStarBank.h"

void ArenaStarBank::unregisterForEvents()
{
}

void ArenaStarBank::initLoadingResourcesGroupList()
{
}

ArenaStarBank::ArenaStarBank()
{
	m_starNum = 0;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArenaStarBank);

void ArenaStarBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArenaStarBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(ArenaStarBank);
}
