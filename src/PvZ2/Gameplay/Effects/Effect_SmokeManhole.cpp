//
//  Effect_SmokeManhole.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SmokeManhole.h"

Effect_SmokeManhole::~Effect_SmokeManhole()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_SmokeManhole);

void Effect_SmokeManhole::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_SmokeManhole);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_SmokeManhole);
}
