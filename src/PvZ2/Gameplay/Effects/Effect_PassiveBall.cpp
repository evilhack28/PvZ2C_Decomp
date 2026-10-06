//
//  Effect_PassiveBall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_OrchidMage.h"

Effect_PassiveBall::Effect_PassiveBall()
{
}

Effect_PassiveBall::~Effect_PassiveBall()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_PassiveBall);

void Effect_PassiveBall::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_PassiveBall);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_PassiveBall);
}
