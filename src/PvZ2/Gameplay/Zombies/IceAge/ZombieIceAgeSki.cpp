//
//  ZombieIceAgeSki.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieIceAgeSki.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeSki);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieIceAgeSkiProps);

void ZombieIceAgeSkiProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieIceAgeSkiProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, ViewDistance);
	REFLECTION_CLASSBUILDER_END(ZombieIceAgeSkiProps);
}

#include "Zombie.h"
void ZombieIceAgeSki::onUpdate()
{
	 Zombie::onUpdate();
}
