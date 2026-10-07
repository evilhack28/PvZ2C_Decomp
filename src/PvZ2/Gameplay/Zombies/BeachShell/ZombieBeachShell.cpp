//
//  ZombieBeachShell.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBeachShell.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBeachShell);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBeachShellProps);

void ZombieBeachShellProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBeachShellProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieBeachShellProps);
}

bool ZombieBeachShell::canTargetEntityHeight(BoardEntityHeight i_entityHeight)
{
	return true;
}
