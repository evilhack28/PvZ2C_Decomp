//
//  ZombieAnimRig_RomanShield.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieRomanShield.h"

ZombieAnimRig_RomanShield::ZombieAnimRig_RomanShield()
{
}

ZombieAnimRig_RomanShield::~ZombieAnimRig_RomanShield()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_RomanShield);

void ZombieAnimRig_RomanShield::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_RomanShield);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Camel);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_RomanShield);
}
