//
//  ZombieHammer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieHammer.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieHammer);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieHammerProps);

void ZombieHammerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieHammerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(bool, AdvanceSpin);
	REFLECTION_CLASSBUILDER_END(ZombieHammerProps);
}

void ZombieHammer::onBlockEnd(Zombie* z)
{
}

ZombieParticle* ZombieHammer::DropArm()
{
	return NULL;
}

void ZombieHammer::onRestEnd(Zombie* z)
{
}
