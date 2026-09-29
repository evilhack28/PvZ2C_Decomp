//
//  ZombieModernAllStar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieModernAllStar.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieModernAllStar);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieModernAllStarProps);

void ZombieModernAllStarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieModernAllStarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, SmashDamage);
		REFLECTION_CLASSBUILDER_FIELD(float, RunningSpeedScale);
	REFLECTION_CLASSBUILDER_END(ZombieModernAllStarProps);
}
