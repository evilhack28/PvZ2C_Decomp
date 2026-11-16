//
//  ZombieQigong.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombieQigong.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieQigong);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieQigongProps);

void ZombieQigongProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieQigongProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieQigongProps);
}

ZombieParticle* ZombieQigong::DropArm()
{
	return NULL;
}
