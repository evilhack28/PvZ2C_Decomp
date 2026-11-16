//
//  ZombieGatlingPea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieGatlingPea.h"

#include "ZombieShooter.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ZombieGatlingPea::ZombieGatlingPea()
{
}

ZombieGatlingPea::~ZombieGatlingPea()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ZombieGatlingPea);

void ZombieGatlingPea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieGatlingPea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieShooter);

	REFLECTION_CLASSBUILDER_END(ZombieGatlingPea);
}

/////////////// Logic ///////////////

void ZombieGatlingPea::onZombieInitialize()
{
	 ZombieShooter::onZombieInitialize();
}
