//
//  ZombieZombossMech_Future.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_Future.h"

ZombieZombossMechFutureProps::~ZombieZombossMechFutureProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMech_Future);

void ZombieZombossMech_Future::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMech_Future);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMech);

	REFLECTION_CLASSBUILDER_END(ZombieZombossMech_Future);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZombossMechFutureProps);

void ZombieZombossMechFutureProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZombossMechFutureProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieZombossMechProps);

	REFLECTION_CLASSBUILDER_END(ZombieZombossMechFutureProps);
}
