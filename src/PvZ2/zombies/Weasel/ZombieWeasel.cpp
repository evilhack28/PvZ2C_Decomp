//
//  ZombieWeasel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieChicken.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieWeasel);

void ZombieWeasel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieWeasel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieChicken);

	REFLECTION_CLASSBUILDER_END(ZombieWeasel);
}
