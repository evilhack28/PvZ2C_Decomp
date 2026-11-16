//
//  ZombieMagicBronze.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMagicBronze.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMagicBronze);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMagicBronzeProps);

void ZombieMagicBronzeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMagicBronzeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(CZombieSummonDataPool, ZombieSummonDataPool);
	REFLECTION_CLASSBUILDER_END(ZombieMagicBronzeProps);
}

ZombieParticle* ZombieMagicBronze::DropArm()
{
	return NULL;
}

#include "Zombie.h"
void ZombieMagicBronze::onUpdate()
{
	 Zombie::onUpdate();
}

#include "Zombie.h"
void ZombieMagicBronze::onDestroy()
{
	 Zombie::onDestroy();
}
