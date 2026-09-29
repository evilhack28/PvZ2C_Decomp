//
//  ZombieCatapult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieCatapult.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCatapult);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieCatapultProps);

void ZombieCatapultProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieCatapultProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<RtObject>, BallProjectile);
	REFLECTION_CLASSBUILDER_END(ZombieCatapultProps);
}

bool ZombieCatapult::canTargetEntityHeight(BoardEntityHeight i_arg)
{
	return true;
}
