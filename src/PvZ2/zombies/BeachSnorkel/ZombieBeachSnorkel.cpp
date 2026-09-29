//
//  ZombieBeachSnorkel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBeachSnorkel.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBeachSnorkel);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBeachSnorkelProps);

void ZombieBeachSnorkelProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieBeachSnorkelProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieBeachSnorkelProps);
}
