//
//  ArenaPlayerBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArenaPlayerBank.h"

void ArenaPlayerBank::registerForEvents()
{
}

void ArenaPlayerBank::unregisterForEvents()
{
}

void ArenaPlayerBank::initLoadingResourcesGroupList()
{
}

void ArenaPlayerBank::onUpdate()
{
}

ArenaPlayerBank::~ArenaPlayerBank()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArenaPlayerBank);

void ArenaPlayerBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArenaPlayerBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(ArenaPlayerBank);
}
