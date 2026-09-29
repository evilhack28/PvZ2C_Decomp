//
//  ZombieEightiesBass.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieEightiesBass.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesBass);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieEightiesBassProps);

void ZombieEightiesBassProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieEightiesBassProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, ShockWaveSpawnOffset);
		REFLECTION_CLASSBUILDER_FIELD(float, ShockWaveSpawnInterval);
	REFLECTION_CLASSBUILDER_END(ZombieEightiesBassProps);
}

#include "Zombie.h"
void ZombieEightiesBass::onZombieInitialize()
{
	 Zombie::onZombieInitialize();
}
