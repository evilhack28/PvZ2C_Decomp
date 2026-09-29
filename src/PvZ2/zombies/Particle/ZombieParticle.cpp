//
//  ZombieParticle.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieParticle.h"

ZombieParticle::ZombieParticle()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieParticle);

void ZombieParticle::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieParticle);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PopAnimRig>, m_zombieRig);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_settled);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_particleName);
	REFLECTION_CLASSBUILDER_END(ZombieParticle);
}
