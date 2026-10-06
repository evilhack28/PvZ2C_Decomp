//
//  ZombieAnimRig_PVPSkill.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePVPSkill.h"

ZombieAnimRig_PVPSkill::ZombieAnimRig_PVPSkill()
{
}

ZombieAnimRig_PVPSkill::~ZombieAnimRig_PVPSkill()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_PVPSkill);

void ZombieAnimRig_PVPSkill::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_PVPSkill);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Basic);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_PVPSkill);
}
