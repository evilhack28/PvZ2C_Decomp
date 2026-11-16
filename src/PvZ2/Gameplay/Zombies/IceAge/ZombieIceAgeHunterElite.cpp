//
//  ZombieIceAgeHunterElite.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeHunter.h"

ZombieIceAgeHunterEliteProps::~ZombieIceAgeHunterEliteProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeHunterElite);

void ZombieIceAgeHunterElite::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeHunterElite);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieIceAgeHunter);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_watchAnimHandle);
		REFLECTION_CLASSBUILDER_FIELD(int, m_skillTimeCount);
	REFLECTION_CLASSBUILDER_END(ZombieIceAgeHunterElite);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeHunterEliteProps);

void ZombieIceAgeHunterEliteProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeHunterEliteProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieIceAgeHunterProps);

		REFLECTION_CLASSBUILDER_FIELD(int, SkillSpecialInterval);
	REFLECTION_CLASSBUILDER_END(ZombieIceAgeHunterEliteProps);
}
