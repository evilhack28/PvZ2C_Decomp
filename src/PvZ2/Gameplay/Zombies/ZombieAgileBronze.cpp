//
//  ZombieAgileBronze.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAgileBronze.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAgileBronze);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAgileBronzeProps);

void ZombieAgileBronzeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAgileBronzeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, GridWidthToJump);
	REFLECTION_CLASSBUILDER_END(ZombieAgileBronzeProps);
}

ZombieParticle* ZombieAgileBronze::DropArm()
{
	return NULL;
}
