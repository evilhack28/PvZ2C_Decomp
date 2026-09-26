//
//  ZombieZombossMech_Cowboy.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_Cowboy.h"

ZombieZombossMechCowboyProps::~ZombieZombossMechCowboyProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMechCowboyProps);

void ZombieZombossMechCowboyProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMechCowboyProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMechProps);

	REFLECTION_CLASSBUILDER_END(ZombieZombossMechCowboyProps);
}
