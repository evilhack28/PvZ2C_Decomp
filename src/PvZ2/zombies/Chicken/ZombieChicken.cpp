//
//  ZombieChicken.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieChicken.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieChicken);

void ZombieChicken::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieChicken);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

	REFLECTION_CLASSBUILDER_END(ZombieChicken);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieChickenProps);

void ZombieChickenProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieChickenProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, BucketPercentage);
		REFLECTION_CLASSBUILDER_FIELD(std::string, ElectrocutePAMName);
		REFLECTION_CLASSBUILDER_FIELD(bool, AffectedBySliders);
	REFLECTION_CLASSBUILDER_END(ZombieChickenProps);
}

void ZombieChicken::onTurnedToAsh()
{
}

void ZombieChicken::CreateZombieLevelEffect(bool i_arg)
{
}
