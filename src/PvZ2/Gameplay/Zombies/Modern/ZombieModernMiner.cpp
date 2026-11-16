//
//  ZombieModernMiner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieModernMiner.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieModernMiner);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieModernMinerProps);

void ZombieModernMinerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieModernMinerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, ExtraSpeed);
	REFLECTION_CLASSBUILDER_END(ZombieModernMinerProps);
}

bool ZombieModernMiner::canBeDamagedByAttack(Plant* i_instigator, DamageTypeFlags i_damageFlags)
{
	return false;
}
