//
//  Effect_SmokePollution.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SmokeManhole.h"

Effect_SmokePollution::~Effect_SmokePollution()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_SmokePollution);

void Effect_SmokePollution::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_SmokePollution);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_SmokePollution);
}
