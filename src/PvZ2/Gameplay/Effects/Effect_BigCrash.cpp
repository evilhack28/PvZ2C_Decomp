//
//  Effect_BigCrash.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemSnowBall.h"

Effect_BigCrash::Effect_BigCrash()
{
}

Effect_BigCrash::~Effect_BigCrash()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_BigCrash);

void Effect_BigCrash::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_BigCrash);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_BigCrash);
}
