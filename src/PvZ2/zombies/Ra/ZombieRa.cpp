//
//  ZombieRa.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombieRa.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRaProps);

void ZombieRaProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieRaProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, MaxClaimedSunCurrency);
	REFLECTION_CLASSBUILDER_END(ZombieRaProps);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieRa);

#include "Zombie.h"
void ZombieRa::onPlaceOnBoard()
{
	 Zombie::onPlaceOnBoard();
}
