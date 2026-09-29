//
//  ZombieModernNewspaper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieModernNewspaper.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieModernNewspaper);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieModernNewspaperProps);

void ZombieModernNewspaperProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieModernNewspaperProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieModernNewspaperProps);
}

#include "Zombie.h"
void ZombieModernNewspaper::registerForEvents()
{
	 Zombie::registerForEvents();
}
