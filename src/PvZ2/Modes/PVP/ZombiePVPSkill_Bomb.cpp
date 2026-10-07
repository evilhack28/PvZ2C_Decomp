//
//  ZombiePVPSkill_Bomb.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPSkill_Bomb.h"

void ZombiePVPSkill_Bomb::updateState_Playing()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePVPSkill_Bomb);

void ZombiePVPSkill_Bomb::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiePVPSkill_Bomb);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePVPSkill);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PVPSkillBombRocket>, m_rocketPtr);
	REFLECTION_CLASSBUILDER_END(ZombiePVPSkill_Bomb);
}

void ZombiePVPSkill_Bomb::onExitState_Playing(ZombieState i_newState)
{
}
