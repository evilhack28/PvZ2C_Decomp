//
//  ZombieSelfExplode.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombieSelfExplode.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSelfExplode);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSelfExplodeProps);

void ZombieSelfExplodeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSelfExplodeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, MaxTorchReach);
	REFLECTION_CLASSBUILDER_END(ZombieSelfExplodeProps);
}

void ZombieSelfExplode::onLostHead()
{
}

void ZombieSelfExplode::onTakeBodyDamage(const DamageInfo& i_damageReceived)
{
}
