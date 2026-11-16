//
//  ZombieHeianNinja.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieHeianNinja.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieHeianNinja);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieHeianNinjaProps);

void ZombieHeianNinjaProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieHeianNinjaProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, SpawnOffset);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
	REFLECTION_CLASSBUILDER_END(ZombieHeianNinjaProps);
}
