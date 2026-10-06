//
//  Effect_Snowdrift.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Artifact.h"

Effect_Snowdrift::Effect_Snowdrift()
{
}

Effect_Snowdrift::~Effect_Snowdrift()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_Snowdrift);

void Effect_Snowdrift::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_Snowdrift);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_Snowdrift);
}
