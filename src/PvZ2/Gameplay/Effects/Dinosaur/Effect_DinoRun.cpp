//
//  Effect_DinoRun.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Effect_DinoRun.h"

Effect_DinoRun::~Effect_DinoRun()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_DinoRun);

void Effect_DinoRun::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_DinoRun);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

		REFLECTION_CLASSBUILDER_FIELD(float, m_spawnDinoInterval);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastUsedDino);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_shadowIgnored);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<EntityWeight>, DinoTypesToSpawn);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Creature>>, m_dinoRunners);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Zombie>>, m_zombiesToBeKilled);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Plant>>, m_plantsToBeKilled);
	REFLECTION_CLASSBUILDER_END(Effect_DinoRun);
}
