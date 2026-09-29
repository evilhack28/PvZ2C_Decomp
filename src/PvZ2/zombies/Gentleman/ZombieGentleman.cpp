//
//  ZombieGentleman.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieGentleman.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieGentleman);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieGentlemanProps);

void ZombieGentlemanProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieGentlemanProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, ViewDistance);
	REFLECTION_CLASSBUILDER_END(ZombieGentlemanProps);
}

void ZombieGentleman::onZombieTossDrop(Zombie* i_arg)
{
}

#include "Zombie.h"
void ZombieGentleman::onUpdate()
{
	 Zombie::onUpdate();
}
