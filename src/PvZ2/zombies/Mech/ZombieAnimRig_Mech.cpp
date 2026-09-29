//
//  ZombieAnimRig_Mech.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_Mech.h"

ZombieAnimRig_Mech::ZombieAnimRig_Mech()
{
}

ZombieAnimRig_Mech::~ZombieAnimRig_Mech()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_Mech);

void ZombieAnimRig_Mech::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_Mech);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Gargantuar);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_Mech);
}

void ZombieAnimRig_Mech::SetDamageState(int i_arg)
{
}

#include "ZombieAnimRig_Mech.h"
void ZombieAnimRig_Mech::onStunStartEnd(const std::string& i_arg)
{
	 ZombieAnimRig_Mech::PlayEMPeachStunIdle();
}
