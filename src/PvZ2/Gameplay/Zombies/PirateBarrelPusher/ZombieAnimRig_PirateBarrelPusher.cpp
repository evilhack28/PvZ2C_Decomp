//
//  ZombieAnimRig_PirateBarrelPusher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_PirateBarrelPusher.h"

ZombieAnimRig_PirateBarrelPusher::ZombieAnimRig_PirateBarrelPusher()
{
	m_hasShield = 1;
}

ZombieAnimRig_PirateBarrelPusher::~ZombieAnimRig_PirateBarrelPusher()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_PirateBarrelPusher);

void ZombieAnimRig_PirateBarrelPusher::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_PirateBarrelPusher);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasShield);
	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_PirateBarrelPusher);
}
