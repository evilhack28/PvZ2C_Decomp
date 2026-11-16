//
//  ZombieRomanShield.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieRomanShield.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRomanShield);

void ZombieRomanShield::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieRomanShield);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieCamel);

	REFLECTION_CLASSBUILDER_END(ZombieRomanShield);
}
