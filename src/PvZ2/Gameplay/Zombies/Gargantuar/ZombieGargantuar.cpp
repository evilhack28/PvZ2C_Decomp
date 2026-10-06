//
//  ZombieGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieGargantuar.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieGargantuar);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieGargantuarProps);

void ZombieGargantuarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieGargantuarProjectilePair);
		REFLECTION_CLASSBUILDER_FIELD(float, HealthPercentThrowImp);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ProjectileLayersToHide);
	REFLECTION_CLASSBUILDER_END(ZombieGargantuarProjectilePair);

	REFLECTION_CLASSBUILDER_BEGIN(ZombieGargantuarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombieGargantuarProjectilePair>, HealthThresholdToImpAmmoLayers);
		REFLECTION_CLASSBUILDER_FIELD(int, ImpTargetColumn);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, ImpSpawnOffset);
	REFLECTION_CLASSBUILDER_END(ZombieGargantuarProps);
}

bool ZombieGargantuar::canTargetEntityHeight(BoardEntityHeight i_arg)
{
	return true;
}

bool ZombieGargantuar::CanBeFlickedOff() const
{
	return false;
}
