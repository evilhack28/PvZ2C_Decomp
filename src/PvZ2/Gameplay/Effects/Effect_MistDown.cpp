//
//  Effect_MistDown.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieYearMonster.h"

Effect_MistDown::~Effect_MistDown()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_MistDown);

void Effect_MistDown::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_MistDown);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_MistDown);
}
