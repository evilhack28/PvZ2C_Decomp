//
//  ZombieSkyCityGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSkyCityGargantuar.h"

ZombieSkyCityGargantuarProps::~ZombieSkyCityGargantuarProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkyCityGargantuar);

void ZombieSkyCityGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSkyCityGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuar);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_bAttackAirShip);
	REFLECTION_CLASSBUILDER_END(ZombieSkyCityGargantuar);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkyCityGargantuarProps);

void ZombieSkyCityGargantuarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSkyCityGargantuarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuarProps);

	REFLECTION_CLASSBUILDER_END(ZombieSkyCityGargantuarProps);
}
