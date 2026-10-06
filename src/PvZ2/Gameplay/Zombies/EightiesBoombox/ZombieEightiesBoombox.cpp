//
//  ZombieEightiesBoombox.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesBoombox.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesBoombox);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesBoomboxProps);

void ZombieEightiesBoomboxProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesBoomboxProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, PlantBoomRestrictionSet);
		REFLECTION_CLASSBUILDER_FIELD(std::string, JamStyle);
		REFLECTION_CLASSBUILDER_FIELD(int, PlantFreezeRadius);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesBoomboxProps);
}

#include "Zombie.h"
void ZombieEightiesBoombox::onZombieInitialize()
{
	 Zombie::onZombieInitialize();
}
