//
//  ZombieGum.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieGum.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieGumProps);

void ZombieGumProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieGumProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(DamageLifetime, DamagePhases);
	REFLECTION_CLASSBUILDER_END(ZombieGumProps);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieGum);
