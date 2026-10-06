//
//  ZombieSwashbuckler.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSwashbuckler.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSwashbuckler);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSwashbucklerProps);

void ZombieSwashbucklerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSwashbucklerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, FallIntoDrinkChance);
	REFLECTION_CLASSBUILDER_END(ZombieSwashbucklerProps);
}
