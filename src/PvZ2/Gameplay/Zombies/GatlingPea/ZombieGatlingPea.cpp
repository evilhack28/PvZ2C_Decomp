//
//  ZombieGatlingPea.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieGatlingPea.h"

#include "ZombieShooter.h"
void ZombieGatlingPea::onZombieInitialize()
{
	 ZombieShooter::onZombieInitialize();
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieGatlingPea);

void ZombieGatlingPea::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieGatlingPea);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieShooter);

	REFLECTION_CLASSBUILDER_END(ZombieGatlingPea);
}

ZombieGatlingPea::ZombieGatlingPea()
{
}

ZombieGatlingPea::~ZombieGatlingPea()
{
}
