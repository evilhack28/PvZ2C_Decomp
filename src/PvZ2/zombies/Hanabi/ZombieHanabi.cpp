//
//  ZombieHanabi.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieHanabi.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieHanabi);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieHanabiProps);

void ZombieHanabiProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieHanabiProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, ExplodeDamage);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
	REFLECTION_CLASSBUILDER_END(ZombieHanabiProps);
}

ZombieParticle* ZombieHanabi::DropArm()
{
	return NULL;
}
