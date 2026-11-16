//
//  ZombieEightiesBreakDancer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesBreakDancer.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesBreakDancer);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesBreakDancerProps);

void ZombieEightiesBreakDancerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesBreakDancerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, JamStyle);
		REFLECTION_CLASSBUILDER_FIELD(Rect, TossTargetRect);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesBreakDancerProps);
}
