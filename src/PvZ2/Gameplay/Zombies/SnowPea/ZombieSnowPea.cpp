//
//  ZombieSnowPea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSnowPea.h"
#include "ReflectionBuilder.h"
#include "ZombieShooter.h"

/////////////// Lifecycle ///////////////

ZombieSnowPea::ZombieSnowPea()
{
}

ZombieSnowPea::~ZombieSnowPea()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieSnowPea);

void ZombieSnowPea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSnowPea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieShooter);

	REFLECTION_CLASSBUILDER_END(ZombieSnowPea);
}

/////////////// Logic ///////////////

void ZombieSnowPea::onZombieInitialize()
{
	 ZombieShooter::onZombieInitialize();
}
