//
//  ZombiePVPSkill.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPSkill.h"

ZombiePVPSkillProps::~ZombiePVPSkillProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPSkill);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPSkillProps);

void ZombiePVPSkillProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePVPSkillProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, SkillScope);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, ReduceCost);
	REFLECTION_CLASSBUILDER_END(ZombiePVPSkillProps);
}

class   BoardEntity* ZombiePVPSkill::findTarget()
{
	return NULL;
}

#include "Zombie.h"
void ZombiePVPSkill::onZombieInitialize()
{
	 Zombie::onZombieInitialize();
}

void ZombiePVPSkill::onExitState_Playing(ZombieState i_arg)
{
}

void ZombiePVPSkill::updateState_Playing()
{
}

void ZombiePVPSkill::onEnterState_Playing(ZombieState i_arg)
{
}

void ZombiePVPSkill::CreateArenaSpawnEffect()
{
}

void ZombiePVPSkill::CreateZombieLevelEffect(bool i_arg)
{
}

#include "Zombie.h"
void ZombiePVPSkill::onUpdate()
{
	 Zombie::onUpdate();
}

bool ZombiePVPSkill::ShouldDrawShadow() const
{
	return false;
}
