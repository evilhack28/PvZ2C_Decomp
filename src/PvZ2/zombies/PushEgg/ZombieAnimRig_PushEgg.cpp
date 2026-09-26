//
//  ZombieAnimRig_PushEgg.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieDinoPushEgg.h"

ZombieAnimRig_PushEgg::ZombieAnimRig_PushEgg()
{
}

ZombieAnimRig_PushEgg::~ZombieAnimRig_PushEgg()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_PushEgg);

void ZombieAnimRig_PushEgg::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_PushEgg);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithPushingActionAnimRig);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_PushEgg);
}
