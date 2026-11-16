//
//  ZombieEightiesGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesGargantuar.h"

ZombieEightiesGargantuarProps::~ZombieEightiesGargantuarProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesGargantuar);

void ZombieEightiesGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuar);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isJamming);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_arbitrarySmashTime);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesGargantuar);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesGargantuarProps);

void ZombieEightiesGargantuarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesGargantuarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuarProps);

		REFLECTION_CLASSBUILDER_FIELD(std::string, JamStyle);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, ShockWaveSpawnOffset);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesGargantuarProps);
}
