//
//  ZombieStrongBronze.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombieStrongBronze.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieStrongBronze);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieStrongBronzeProps);

void ZombieStrongBronzeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieStrongBronzeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieStrongBronzeProps);
}

ZombieParticle* ZombieStrongBronze::DropArm()
{
	return NULL;
}
