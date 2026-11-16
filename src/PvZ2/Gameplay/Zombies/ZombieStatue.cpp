//
//  ZombieStatue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieStatue.h"

ZombieStatueProps::~ZombieStatueProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieStatue);

void ZombieStatue::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieStatue);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

	REFLECTION_CLASSBUILDER_END(ZombieStatue);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieStatueProps);

void ZombieStatueProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieStatueProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(DamageLifetime, DamagePhases);
		REFLECTION_CLASSBUILDER_FIELD(std::string, BreakEffect);
	REFLECTION_CLASSBUILDER_END(ZombieStatueProps);
}

void ZombieStatue::onApplyCondition(ZombieConditions i_condition)
{
}
