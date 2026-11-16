//
//  ZombieAnimRig_CoalCart.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSteamCoalCart.h"

ZombieAnimRig_CoalCart::ZombieAnimRig_CoalCart()
{
}

ZombieAnimRig_CoalCart::~ZombieAnimRig_CoalCart()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_CoalCart);

void ZombieAnimRig_CoalCart::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_CoalCart);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasCart);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_CoalCart);
}
