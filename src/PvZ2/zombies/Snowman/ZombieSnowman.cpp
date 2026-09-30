//
//  ZombieSnowman.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieSnowman.h"

#include "Zombie.h"
void ZombieSnowman::onZombieInitialize()
{
	 Zombie::onZombieInitialize();
}

void ZombieSnowman::onAttackAnimStopped(const std::string& i_arg)
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieSnowman);

void ZombieSnowman::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieSnowman);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

	REFLECTION_CLASSBUILDER_END(ZombieSnowman);
}

BoardEntity * ZombieSnowman::findTarget()
{
	return NULL;
}

bool ZombieSnowman::hasArmParticle() const
{
	return false;
}

bool ZombieSnowman::hasHeadParticle() const
{
	return false;
}

bool ZombieSnowman::ShouldDrawShadow() const
{
	return false;
}
