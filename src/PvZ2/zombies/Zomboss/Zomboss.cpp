//
//  Zomboss.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Zomboss.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombossProps);

void ZombossProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombossProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, ZombossStageCount);
	REFLECTION_CLASSBUILDER_END(ZombossProps);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Zomboss);

void Zomboss::chooseDeathState(const DamageInfo& i_arg)
{
}
