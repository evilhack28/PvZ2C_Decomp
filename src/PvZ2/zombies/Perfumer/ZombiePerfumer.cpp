//
//  ZombiePerfumer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePerfumer.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePerfumer);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePerfumerProps);

void ZombiePerfumerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePerfumerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, _throwChargeTimeThreshold);
	REFLECTION_CLASSBUILDER_END(ZombiePerfumerProps);
}
