//
//  ZombieAnimRig_RomanTopShield.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieRomanShield.h"

ZombieAnimRig_RomanTopShield::ZombieAnimRig_RomanTopShield()
{
}

ZombieAnimRig_RomanTopShield::~ZombieAnimRig_RomanTopShield()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_RomanTopShield);

void ZombieAnimRig_RomanTopShield::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_RomanTopShield);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Camel);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_RomanTopShield);
}

ZombieParticle* ZombieAnimRig_RomanTopShield::CreateProjectileParticle()
{
	ZombieAnimRig* aRig = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("roman")->CreateAnimRig();
	return aRig->SpawnProjectileParticle();
}

