//
//  ZombieIceAgeHunter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeHunter.h"

ZombieIceAgeHunterProps::ZombieIceAgeHunterProps()
{
	NearAttackRange = (decltype(NearAttackRange))4;
	FarAttackRange = (decltype(FarAttackRange))7;
	SnowballsPerBarrage = (decltype(SnowballsPerBarrage))3;
}

ZombieIceAgeHunterProps::~ZombieIceAgeHunterProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeHunter);

void ZombieIceAgeHunter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeHunter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActions);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextCastTime);
	REFLECTION_CLASSBUILDER_END(ZombieIceAgeHunter);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeHunterProps);

void ZombieIceAgeHunterProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeHunterProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActionsProps);

	REFLECTION_CLASSBUILDER_END(ZombieIceAgeHunterProps);
}
