//
//  ZombieExplodenut.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieExplodenut.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieExplodenut);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieExplodenutProps);

void ZombieExplodenutProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieExplodenutProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, ExplodeDamage);
	REFLECTION_CLASSBUILDER_END(ZombieExplodenutProps);
}
