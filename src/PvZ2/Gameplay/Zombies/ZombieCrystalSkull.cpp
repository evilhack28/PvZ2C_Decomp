//
//  ZombieCrystalSkull.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityCrystalSkull.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCrystalSkull);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCrystalSkullProps);

void ZombieCrystalSkullProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieCrystalSkullProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieCrystalSkullProps);
}
