//
//  PowerupFlickZombie.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PowerupFlickZombie.h"

PowerupFlickZombie::~PowerupFlickZombie()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupFlickZombie);

void PowerupFlickZombie::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupFlickZombie);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BasePowerup);

	REFLECTION_CLASSBUILDER_END(PowerupFlickZombie);
}
