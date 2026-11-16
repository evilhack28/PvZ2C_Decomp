//
//  ZombieTombRaiser.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombieTombRaiser.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieTombRaiser);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieTombRaiserProps);

void ZombieTombRaiserProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieTombRaiserProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int32, NumberOfTombsToSpawn);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
	REFLECTION_CLASSBUILDER_END(ZombieTombRaiserProps);
}
