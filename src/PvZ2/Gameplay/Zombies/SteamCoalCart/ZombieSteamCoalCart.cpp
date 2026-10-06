//
//  ZombieSteamCoalCart.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSteamCoalCart.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSteamCoalCart);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSteamCoalCartProps);

void ZombieSteamCoalCartProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSteamCoalCartProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieSteamCoalCartProps);
}

#include "Zombie.h"
void ZombieSteamCoalCart::registerForEvents()
{
	 Zombie::registerForEvents();
}
