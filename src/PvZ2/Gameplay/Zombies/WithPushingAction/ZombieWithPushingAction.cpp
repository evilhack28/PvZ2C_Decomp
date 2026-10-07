//
//  ZombieWithPushingAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieWithPushingAction.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieWithPushingAction);

void ZombieWithPushingAction::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieWithPushingAction);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieWithActions);

		REFLECTION_CLASSBUILDER_FIELD(int, m_numberOfIGriditemsToSpawnWith);
	REFLECTION_CLASSBUILDER_END(ZombieWithPushingAction);
}

void ZombieWithPushingAction::spawnGridItemThatZombiePushes(int32_t column)
{
}
