//
//  ZombieIceAgeArmor3Elite.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceageBasic.h"

ZombieIceAgeArmor3ElitePropertySheet::~ZombieIceAgeArmor3ElitePropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeArmor3ElitePropertySheet);

void ZombieIceAgeArmor3ElitePropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeArmor3ElitePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieIceAgeArmor3ElitePropertySheet);
}
