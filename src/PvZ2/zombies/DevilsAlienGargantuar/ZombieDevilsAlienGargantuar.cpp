//
//  ZombieDevilsAlienGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_DevilsFlower.h"

ZombieDevilsAlienGargantuarProps::~ZombieDevilsAlienGargantuarProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieDevilsAlienGargantuar);

void ZombieDevilsAlienGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieDevilsAlienGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuar);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_isOutBoard);
	REFLECTION_CLASSBUILDER_END(ZombieDevilsAlienGargantuar);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieDevilsAlienGargantuarProps);

void ZombieDevilsAlienGargantuarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieDevilsAlienGargantuarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuarProps);

		REFLECTION_CLASSBUILDER_FIELD(float, SpawnSlimeRatio);
		REFLECTION_CLASSBUILDER_FIELD(Rect, SpawnSlimeRect);
		REFLECTION_CLASSBUILDER_FIELD(ProjectilePropertySheetPtr, Projectile);
	REFLECTION_CLASSBUILDER_END(ZombieDevilsAlienGargantuarProps);
}

bool ZombieDevilsAlienGargantuar::isImpReadyToBeThrown()
{
	return false;
}
