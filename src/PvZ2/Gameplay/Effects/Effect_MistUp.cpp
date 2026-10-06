//
//  Effect_MistUp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieYearMonster.h"

Effect_MistUp::~Effect_MistUp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_MistUp);

void Effect_MistUp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_MistUp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_MistUp);
}
