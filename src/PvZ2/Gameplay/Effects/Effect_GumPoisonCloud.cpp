//
//  Effect_GumPoisonCloud.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieGum.h"

Effect_GumPoisonCloud::Effect_GumPoisonCloud()
{
}

Effect_GumPoisonCloud::~Effect_GumPoisonCloud()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_GumPoisonCloud);

void Effect_GumPoisonCloud::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_GumPoisonCloud);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_targetZombie);

	REFLECTION_CLASSBUILDER_END(Effect_GumPoisonCloud);
}
