//
//  ZombieCardGameSelfExplode.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCardGameSelfExplode.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCardGameSelfExplode);

void ZombieCardGameSelfExplode::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieCardGameSelfExplode);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSelfExplode);

	REFLECTION_CLASSBUILDER_END(ZombieCardGameSelfExplode);
}
