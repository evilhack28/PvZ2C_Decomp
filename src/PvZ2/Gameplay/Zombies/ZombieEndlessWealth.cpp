//
//  ZombieEndlessWealth.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEndlessWealth.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEndlessWealth);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEndlessWealthProps);

void ZombieEndlessWealthProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEndlessWealthProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, MoveTime);
	REFLECTION_CLASSBUILDER_END(ZombieEndlessWealthProps);
}
