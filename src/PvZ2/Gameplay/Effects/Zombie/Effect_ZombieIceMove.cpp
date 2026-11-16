//
//  Effect_ZombieIceMove.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Zombie_IceYearMonster.h"

Effect_ZombieIceMove::~Effect_ZombieIceMove()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_ZombieIceMove);

void Effect_ZombieIceMove::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_ZombieIceMove);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_ZombieIceMove);
}
