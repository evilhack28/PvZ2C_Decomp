//
//  ZombieEightiesArcade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesArcade.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesArcade);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesArcadeProps);

void ZombieEightiesArcadeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesArcadeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, JamStyle);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesArcadeProps);
}
