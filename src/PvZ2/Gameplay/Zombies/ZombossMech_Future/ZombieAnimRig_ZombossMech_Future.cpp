//
//  ZombieAnimRig_ZombossMech_Future.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAnimRig_ZombossMech_Future.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ZombossMech_Future);

void ZombieAnimRig_ZombossMech_Future::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ZombossMech_Future);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_ZombossMech);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ZombossMech_Future);
}

ZombieAnimRig_ZombossMech_Future::ZombieAnimRig_ZombossMech_Future()
{
	m_queuedTileClass = POWERTILE_Invalid;
}

void ZombieAnimRig_ZombossMech_Future::SetRocketStartAnimFromTileType(PowerTileClass i_class)
{
	m_queuedTileClass = i_class;
}

const char* ZombieAnimRig_ZombossMech_Future::getRocketStartAnimName() const
{
	switch ((int)m_queuedTileClass)
	{
	case POWERTILE_ALPHA:
		return "linktile1_start";
	case POWERTILE_BETA:
		return "linktile2_start";
	case POWERTILE_GAMMA:
		return "linktile3_start";
	case POWERTILE_DELTA:
		return "linktile4_start";
	case POWERTILE_EPSILON:
		return "linktile5_start";
	case POWERTILE_Invalid:
		return ZombieAnimRig_ZombossMech::getRocketStartAnimName();
	default:
		return ZombieAnimRig_ZombossMech::getRocketStartAnimName();
	}
}

