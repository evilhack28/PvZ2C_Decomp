//
//  StarChallengeKillZombiesInTime.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "StarChallengeKillZombiesInTime.h"

StarChallengeKillZombiesInTime::~StarChallengeKillZombiesInTime()
{
}

StarChallengeKillZombiesInTimeProps::~StarChallengeKillZombiesInTimeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeKillZombiesInTime);

void StarChallengeKillZombiesInTime::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeKillZombiesInTime);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Challenge);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<pvztime_t>, m_zombiesKilled);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<UIWidget>, m_comboMeter);
	REFLECTION_CLASSBUILDER_END(StarChallengeKillZombiesInTime);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(StarChallengeKillZombiesInTimeProps);

void StarChallengeKillZombiesInTimeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(StarChallengeKillZombiesInTimeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, ZombiesToKill);
		REFLECTION_CLASSBUILDER_FIELD(float, Time);
	REFLECTION_CLASSBUILDER_END(StarChallengeKillZombiesInTimeProps);
}
