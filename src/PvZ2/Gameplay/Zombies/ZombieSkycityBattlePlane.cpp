//
//  ZombieSkycityBattlePlane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSkycityBattlePlane.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkycityBattlePlane);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSkycityBattlePlaneProps);

void ZombieSkycityBattlePlaneProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSkycityBattlePlaneProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieTargetProps);

	REFLECTION_CLASSBUILDER_END(ZombieSkycityBattlePlaneProps);
}

#include "Zombie.h"
class   BoardEntity* ZombieSkycityBattlePlane::findTarget()
{
	return Zombie::findTarget();
}
