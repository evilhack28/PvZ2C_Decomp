//
//  ZombiePVPSkill_Sleep.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPSkill_Sleep.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPSkill_Sleep);

void ZombiePVPSkill_Sleep::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePVPSkill_Sleep);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePVPSkill);

	REFLECTION_CLASSBUILDER_END(ZombiePVPSkill_Sleep);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPSkillSleepProps);

void ZombiePVPSkillSleepProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePVPSkillSleepProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePVPSkillProps);

		REFLECTION_CLASSBUILDER_FIELD(float, SleepTime);
	REFLECTION_CLASSBUILDER_END(ZombiePVPSkillSleepProps);
}
