//
//  ZombieCardGameCavalry.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCardGameCavalry.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCardGameCavalry);

void ZombieCardGameCavalry::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieCardGameCavalry);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieCavalry);

	REFLECTION_CLASSBUILDER_END(ZombieCardGameCavalry);
}
