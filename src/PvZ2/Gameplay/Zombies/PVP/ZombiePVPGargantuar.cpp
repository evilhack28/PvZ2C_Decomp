//
//  ZombiePVPGargantuar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPGargantuar.h"

#include "Zombie.h"
void ZombiePVPGargantuar::ApplyZombieFood()
{
	 Zombie::ApplyZombieFood();
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPGargantuar);

void ZombiePVPGargantuar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePVPGargantuar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieGargantuar);

	REFLECTION_CLASSBUILDER_END(ZombiePVPGargantuar);
}
