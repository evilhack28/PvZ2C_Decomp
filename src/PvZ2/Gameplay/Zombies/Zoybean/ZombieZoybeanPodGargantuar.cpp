//
//  ZombieZoybeanPodGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZoybeanPodGargantuar.h"

ZombieZoybeanPodGargantuarProps::~ZombieZoybeanPodGargantuarProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZoybeanPodGargantuar);

void ZombieZoybeanPodGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZoybeanPodGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuar);

		REFLECTION_CLASSBUILDER_FIELD(float, additionalDamage);
	REFLECTION_CLASSBUILDER_END(ZombieZoybeanPodGargantuar);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZoybeanPodGargantuarProps);

void ZombieZoybeanPodGargantuarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZoybeanPodGargantuarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuarProps);

		REFLECTION_CLASSBUILDER_FIELD(float, pauseDuration);
	REFLECTION_CLASSBUILDER_END(ZombieZoybeanPodGargantuarProps);
}

bool ZombieZoybeanPodGargantuar::isImpReadyToBeThrown()
{
	return false;
}
