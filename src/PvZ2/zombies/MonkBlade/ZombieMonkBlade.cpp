//
//  ZombieMonkBlade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieMonkBlade.h"
#include "ZombiePropertySheet.h"

ZombieMonkBladeProps::~ZombieMonkBladeProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMonkBlade);

void ZombieMonkBlade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMonkBlade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

		REFLECTION_CLASSBUILDER_FIELD(bool, targetHasDied);
	REFLECTION_CLASSBUILDER_END(ZombieMonkBlade);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieMonkBladeProps);

void ZombieMonkBladeProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieMonkBladeProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieMonkBladeProps);
}

void ZombieMonkBlade::updateState_Eat()
{
}

#include "Zombie.h"
void ZombieMonkBlade::onUpdate()
{
	 Zombie::onUpdate();
}
