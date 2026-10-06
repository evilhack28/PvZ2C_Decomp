//
//  ZombieEightiesBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesBasic.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesBasic);

void ZombieEightiesBasic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesBasic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieBasic);

	REFLECTION_CLASSBUILDER_END(ZombieEightiesBasic);
}
