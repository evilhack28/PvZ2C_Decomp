//
//  ZombieAnimRig_ZombossMech_PVZ1_Robot.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZombossMech_PVZ1_Robot.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossMech_PVZ1_Robot);

void ZombieAnimRig_ZombossMech_PVZ1_Robot::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossMech_PVZ1_Robot);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ZombossMech);

	REFLECTION_CLASSBUILDER_FIELD(int, m_damagePhase);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossMech_PVZ1_Robot);
}
